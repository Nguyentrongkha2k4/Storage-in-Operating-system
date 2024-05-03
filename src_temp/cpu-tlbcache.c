/*
 * Copyright (C) 2024 pdnguyen of the HCMC University of Technology
 */
/*
 * Source Code License Grant: Authors hereby grants to Licensee 
 * a personal to use and modify the Licensed Source Code for 
 * the sole purpose of studying during attending the course CO2018.
 */
//#ifdef MM_TLB
/*
 * Memory physical based TLB Cache
 * TLB cache module tlb/tlbcache.c
 *
 * TLB cache is physically memory phy
 * supports random access 
 * and runs at high speed
 */


#include "mm.h"
#include <stdlib.h>
// #define TLB_SIZE 1024

// struct framephy_struct * tlb[TLB_SIZE];
// #define init_tlbcache(mp,sz,...) init_memphy(mp, sz, (1, ##__VA_ARGS__))

// struct framephy_struct *hash_function(struct memphy_struct *mp, int pid, int pgnum) {
//    int index = (pid ^ pgnum) % TLB_SIZE; // XOR pid and pgnum and then modulo by TLB size
//    return tlb[index];
// }
/*
 *  tlb_cache_read read TLB cache device
 *  @mp: memphy struct
 *  @pid: process id
 *  @pgnum: page number
 *  @value: obtained value
 */
int tlb_cache_read(struct memphy_struct * tlb, int pid, int pgnum, BYTE * value)
{
   /* TODO: the identify info is mapped to 
    *      cache line by employing:
    *      direct mapped, associated mapping etc.
   */
   if (tlb == NULL || value == NULL){
      return -1;
   }
   uint32_t index = (uint32_t)pgnum % tlb->maxsz;
   if(tlb->storage[index] == -1){
      //* do not have that entry in tlb, fail to read
      //* update the tlb entries outside this function
      return -1;
   }

   // if(pid != tlb->pid_hold){
   //    tlb_flush_tlb_of(proc, tlb);
   //    return 0;
   // }

   *value = tlb->storage[index];
   return 0;
}
// int tlb_cache_read(struct memphy_struct *mp, int pid, int pgnum, BYTE *value) {
//    /* TODO: the identify info is mapped to
//     *      cache line by employing:
//     *      direct mapped, associated mapping etc.
//     */
//    // Use a hash function or direct mapping to find the frame
//    struct framephy_struct *frame = hash_function(mp, pid, pgnum);
//    // Check if the frame is valid and matches the pid and pgnum
//    if (frame != NULL && frame->owner->pgd[pgnum] == pid) {
//       // TLB hit, retrieve the value
//       *value = mp->storage[frame->fpn];
//       return 0; // Success
//    }
//    else {
//       // TLB miss, handle accordingly
//       // ...
//       return -1; // Indicate TLB miss
//    }
// }
/*
 *  tlb_cache_write write TLB cache device
 *  @mp: memphy struct
 *  @pid: process id
 *  @pgnum: page number
 *  @value: obtained value
 */
int tlb_cache_write(struct memphy_struct *tlb, int pid, int pgnum, BYTE value)
{
   /* TODO: the identify info is mapped to 
    *      cache line by employing:
    *      direct mapped, associated mapping etc.
    */
      if (tlb == NULL) {
        return -1;  // Return error if the input pointer is invalid
    }
   // if(pid != tlb->pid_hold){
   //    tlb_flush_tlb_of(proc, tlb);
   //    //* update pid hold
   //    tlb->pid_hold = pid;
   //    return 0;
   // }
   uint32_t index = (uint32_t)pgnum % tlb->maxsz;
   tlb->storage[index] = value;  // Store the value in the cache
   return 0;
}
// int tlb_cache_write(struct memphy_struct *mp, int pid, int pgnum, BYTE value) {
//    /* TODO: the identify info is mapped to
//     *      cache line by employing:
//     *      direct mapped, associated mapping etc.
//     */
//    // Use a hash function or direct mapping to find the frame
//    struct framephy_struct *frame = hash_function(mp, pid, pgnum);
//    // Check if the frame is valid and matches the pid and pgnum
//    if (frame != NULL && frame->owner->pgd[pgnum] == pid) {
//        // TLB hit, update the value
//        mp->storage[frame->fpn] = value;
//        return 0; // Success
//    } else {
//        // TLB miss, handle accordingly
//        // ...
//        return -1; // Indicate TLB miss
//    }
// }
/*
 *  TLBMEMPHY_read natively supports MEMPHY device interfaces
 *  @mp: memphy struct
 *  @addr: address
 *  @value: obtained value
 */
int TLBMEMPHY_read(struct memphy_struct * mp, int addr, BYTE *value)
{
   if (mp == NULL)
     return -1;

   /* TLB cached is random access by native */
   *value = mp->storage[addr];

   return 0;
}


/*
 *  TLBMEMPHY_write natively supports MEMPHY device interfaces
 *  @mp: memphy struct
 *  @addr: address
 *  @data: written data
 */
int TLBMEMPHY_write(struct memphy_struct * mp, int addr, BYTE data)
{
   if (mp == NULL)
     return -1;

   /* TLB cached is random access by native */
   mp->storage[addr] = data;

   return 0;
}

/*
 *  TLBMEMPHY_format natively supports MEMPHY device interfaces
 *  @mp: memphy struct
 */


int TLBMEMPHY_dump(struct memphy_struct * mp)
{
   /*TODO dump memphy contnt mp->storage 
    *     for tracing the memory content
    */
   for (int i = 0; i < mp->maxsz; i++) {
        printf("TLB Entry %d: %d\n", i, mp->storage[i]);
   }
   return 0;
}


/*
 *  Init TLBMEMPHY struct
 */
int init_tlbmemphy(struct memphy_struct *mp, int max_size)
{
   mp->storage = (BYTE *)malloc(max_size*sizeof(BYTE));
   mp->maxsz = max_size;
   // mp->pid_hold = -1;

   mp->rdmflg = 1;

   return 0;
}

//#endif
