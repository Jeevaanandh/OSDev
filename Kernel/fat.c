//
// Created by Jeevaanandh Ilayaraja on 26/02/26.
//

#include <stddef.h>
#include <stdint.h>

void traverseFAT(int16_t cluster, int32_t size);
typedef struct {
    uint8_t jump[3];
    uint8_t oem[8];
    uint16_t bytesPerSector;
    uint8_t sectorsPerCluster;
    uint16_t reservedSectors;
    uint8_t numOfFATs;
    uint16_t rootEntryCount;
    uint16_t totalSectors16;
    uint8_t mediaDescriptor;
    uint16_t sectorsPerFAT;
    uint16_t sectorsPerTrack;
    uint16_t numberOfHeads;
    uint32_t hiddenSectors;
    uint32_t totalSectors32;

} __attribute__((packed)) BootSector;


typedef struct {
    uint8_t name[11];
    uint8_t attr;
    uint8_t res;
    uint8_t creationTimeTenths;
    uint16_t creationTime;
    uint16_t creationDate;
    uint16_t lastAccessedDate;
    uint16_t high16OfCluster;   //Not used for FAT16
    uint16_t lastModifiedTime;
    uint16_t lastModifiedDate;
    uint16_t low16OfCluster;
    uint32_t fileSize;

} __attribute__((packed)) RootDirectoryEntry;



int memcmp(const void *s1, const void *s2, size_t n) {
    char *c1= (char *)s1;
    char *c2= (char *)s2;

    for (int i=0;i<n; i++) {
        if (c1[i]!=c2[i]) {
            return c1[i]-c2[i];
        }

    }
    return 0;
}


void findFile() {
    RootDirectoryEntry *root= (RootDirectoryEntry *)0x0900;

    char filename[11]= "BOOT2   BIN";
    for(int i=0; i<512; i++) {
        if (memcmp(root[i].name, filename, 11) == 0) {

            int16_t cluster= root[i].low16OfCluster;
            int32_t size= root[i].fileSize;
            traverseFAT(cluster, size);

        }


    }
}


void traverseFAT(int16_t cluster, int32_t size) {
    uint16_t *FAT= (uint16_t *)0x0500;


}
