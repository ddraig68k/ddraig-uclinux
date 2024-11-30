#include <linux/module.h>
#include <linux/types.h>
#include <linux/mm.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/printk.h>
#include <asm/ddraig.h>

static u8 ddraig_ide_read_status(ide_hwif_t *hwif)
{
    return MEM(DDRAIG_IDE_STATUS);
}

static void ddraig_ide_exec_command(ide_hwif_t *hwif, u8 cmd)
{
    MEM(DDRAIG_IDE_COMMAND) = cmd;
}

static u8 ddraig_ide_read_altstatus(ide_hwif_t *hwif)
{
    return MEM(DDRAIG_IDE_ALT_STATUS);
}

static void ddraig_ide_write_devctl(ide_hwif_t *hwif, u8 ctl)
{
    MEM(DDRAIG_IDE_ALT_STATUS) = ctl;
}

static void ddraig_ide_dev_select(ide_drive_t *drive)
{
    u8 select = drive->select | ATA_DEVICE_OBS;
    MEM(DDRAIG_IDE_DRIVE_SEL) = select;
}

static void ddraig_ide_tf_load(ide_drive_t *drive, struct ide_taskfile *tf, u8 valid)
{
    if (valid & IDE_VALID_FEATURE)
        MEM(DDRAIG_IDE_FEATURE) = tf->feature;
    if (valid & IDE_VALID_NSECT)
        MEM(DDRAIG_IDE_SECTOR_COUNT) = tf->nsect;
    if (valid & IDE_VALID_LBAL)
        MEM(DDRAIG_IDE_SECTOR_START) = tf->lbal;
    if (valid & IDE_VALID_LBAM)
        MEM(DDRAIG_IDE_LBA_MID) = tf->lbam;
    if (valid & IDE_VALID_LBAH)
        MEM(DDRAIG_IDE_LBA_HIGH) = tf->lbah;
    if (valid & IDE_VALID_DEVICE)
        MEM(DDRAIG_IDE_DRIVE_SEL) = tf->device;
}

static void ddraig_ide_tf_read(ide_drive_t *drive, struct ide_taskfile *tf, u8 valid)
{
    if (valid & IDE_VALID_ERROR)
        tf->error = MEM(DDRAIG_IDE_FEATURE);
    if (valid & IDE_VALID_NSECT)
        tf->nsect = MEM(DDRAIG_IDE_SECTOR_COUNT);
    if (valid & IDE_VALID_LBAL)
        tf->lbal = MEM(DDRAIG_IDE_SECTOR_START);
    if (valid & IDE_VALID_LBAM)
        tf->lbam = MEM(DDRAIG_IDE_LBA_MID);
    if (valid & IDE_VALID_LBAH)
        tf->lbah = MEM(DDRAIG_IDE_LBA_HIGH);
    if (valid & IDE_VALID_DEVICE)
        tf->device = MEM(DDRAIG_IDE_DRIVE_SEL);
}

static void ddraig_ide_input_data(ide_drive_t *drive, struct ide_cmd *cmd, void *buf, unsigned int len)
{
    int i;
    int count = (len + 1) / 2;
    u16 *ptr = (u16 *)buf;

    for (i = 0; i < count; i++)
    {
        ptr[i] = MEM16(DDRAIG_IDE_DATA);
    }
}

static void ddraig_ide_output_data(ide_drive_t *drive, struct ide_cmd *cmd, void *buf, unsigned int len)
{
    int i;
    int count = (len + 1) / 2;
    u16 *ptr = (u16 *)buf;

    for (i = 0; i < count; i++)
    {
        MEM16(DDRAIG_IDE_DATA) = ptr[i];
    }
}

static const struct ide_tp_ops ddraig_ide_tp_ops = {
    .read_status = ddraig_ide_read_status,
    .exec_command = ddraig_ide_exec_command,
    .read_altstatus = ddraig_ide_read_altstatus,
    .write_devctl = ddraig_ide_write_devctl,
    .dev_select = ddraig_ide_dev_select,
    .tf_load = ddraig_ide_tf_load,
    .tf_read = ddraig_ide_tf_read,
    .input_data = ddraig_ide_input_data,
    .output_data = ddraig_ide_output_data,
};

static const struct ide_port_info ddraig_ide_port_info = {
    .tp_ops = &ddraig_ide_tp_ops,
    .host_flags = IDE_HFLAG_NO_DMA,
    .chipset = ide_generic,
};

static int __init ddraig_ide_init(void)
{
    struct ide_host *host;
    struct ide_hw hw, *hws[] = {&hw};
    int rc;

    printk(KERN_INFO "Y Dddraig IDE driver\n");

    memset(&hw, 0, sizeof(hw));

    hw.irq = IRQ_NUM_IDE;
    hw.io_ports.data_addr = DDRAIG_IDE_BASE;

    host = ide_host_alloc(&ddraig_ide_port_info, hws, 1);
    if (host == NULL)
    {
        rc = -ENOMEM;
        return rc;
    }

    rc = ide_host_register(host, &ddraig_ide_port_info, hws);

    if (rc)
    {
        ide_host_free(host);
        return rc;
    }

    return 0;
}

module_init(ddraig_ide_init);

MODULE_DESCRIPTION("Y Ddraig IDE Driver");
MODULE_AUTHOR("Stephen Moody");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
