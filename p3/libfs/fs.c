#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "disk.h"
#include "fs.h"

/* TODO: Phase 1 */

struct  __attribute__((__packed__)) superBlock {
	char	 signature[8];
	uint16_t total_Block_counter;
	uint16_t Root_Dir;
	uint16_t Data_Block;
	uint16_t Amout_Data_Block;
	uint8_t  Fat_block;
	uint8_t padding [4079];
};

struct  __attribute__((__packed__)) fatBlock {
	uint16_t Fat_Block_index;
	// fat_block_index[1]
};

struct  __attribute__((__packed__)) rootDir {
	char Filename[FS_FILENAME_LEN];
	uint32_t file_Size;
	uint16_t index;
	uint8_t padding[10];
};



int fs_mount(const char *diskname)
{
	struct superBlock *sb = malloc(sizeof(struct superBlock));
	memeset(sb, 0, BLOCK_SIZE);
	struct fatBlock *Fb = malloc(sizeof(struct fatBlock));
	memeset(Fb, 0, BLOCK_SIZE);
	struct rootDir *rd = malloc (sizeof(struct rootDir));
	memeset(rd, 0, BLOCK_SIZE);
	/* TODO: Phase 1 */
	int open = block_disk_open(diskname);
	if(open == -1){
		return -1;
	}
	if(block_read(0, &sb) == -1){
		return -1;
	}
	
	if(!strcomp(sb->signature,"ECS150FS", 8)){
		return -1;
	}
	if(sb->total_Block_counter != block_disk_count()){
		return -1;
	}
	




}

int fs_umount(void)
{
	/* TODO: Phase 1 */
}

int fs_info(void)
{
	/* TODO: Phase 1 

	printf("FS info: \n");
	printf("Virtual Desk %i\n", sb.VD_Block);
	printf("Root Dir %i\n", sb.Root_Dir);
	printf("Data Block %i\n", sb.Data_Block);
	printf("Amout of Data Block %i\n", sb.Amout_Data_Block);
	printf("Number of Fat %i\n", sb.Fat_Number);
	printf("Padding %i\n", sb.padding);

*/
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

