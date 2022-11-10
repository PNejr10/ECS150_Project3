#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "disk.h"
#include "fs.h"

/* TODO: Phase 1 */

struct  __attribute__((__packed__)) superBlock {
	uint8_t signature;
	uint16_t VD_Block;
	uint16_t Root_Dir;
	uint16_t Data_Block;
	uint16_t Amout_Data_Block;
	uint8_t  Fat_Number;
	uint8_t padding [4079];
};

struct  __attribute__((__packed__)) fatBlock {
	uint16_t *Fat_array;
};

struct  __attribute__((__packed__)) rootDir {
	uint8_t Filename[FS_FILENAME_LEN];
	uint32_t file_Size;
	uint16_t index;
	uint8_t padding[10];
};

struct superBlock sb;
struct fatBlock Fb;
struct rootDir rd;

int fs_mount(const char *diskname)
{
	/* TODO: Phase 1 */
	int open = block_disk_open(diskname);
	if(open == -1){
		printf("Unable to open the Disk\n");
		return -1;
	}
	if(block_read(0, &sb) == -1){
		printf("Could not read the block\n");
	}
	

}

int fs_umount(void)
{
	/* TODO: Phase 1 */
}

int fs_info(void)
{
	/* TODO: Phase 1 */

	printf("FS info: \n");
	printf("Virtual Desk %i\n", sb.VD_Block);
	printf("Root Dir %i\n", sb.Root_Dir);
	printf("Data Block %i\n", sb.Data_Block);
	printf("Amout of Data Block %i\n", sb.Amout_Data_Block);
	printf("Number of Fat %i\n", sb.Fat_Number);
	printf("Padding %i\n", sb.padding);

}

int fs_create(const char *filename)
{
	/* TODO: Phase 2 */
}

int fs_delete(const char *filename)
{
	/* TODO: Phase 2 */
}

int fs_ls(void)
{
	/* TODO: Phase 2 */
}

int fs_open(const char *filename)
{
	/* TODO: Phase 3 */
}

int fs_close(int fd)
{
	/* TODO: Phase 3 */
}

int fs_stat(int fd)
{
	/* TODO: Phase 3 */
}

int fs_lseek(int fd, size_t offset)
{
	/* TODO: Phase 3 */
}

int fs_write(int fd, void *buf, size_t count)
{
	/* TODO: Phase 4 */
}

int fs_read(int fd, void *buf, size_t count)
{
	/* TODO: Phase 4 */
}

