/*
 * Copyright 1996, 1997, 1998 Hans Reiser, see reiserfs/README for licensing and copyright details
 */

				/* this file has an amazingly stupid
                                   name, yura please fix it to be
                                   reiserfs.h, and merge all the rest
                                   of our .h files that are in this
                                   directory into it.  */


#ifndef _LINUX_REISER_FS_H
#define _LINUX_REISER_FS_H

#include <linux/types.h>
#ifdef __KERNEL__
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <asm/unaligned.h>
#include <linux/bitops.h>
#include <linux/proc_fs.h>
#include <linux/smp_lock.h>
#include <linux/buffer_head.h>
#include <linux/reiserfs_fs_i.h>
#include <linux/reiserfs_fs_sb.h>
#endif

/*
 *  include/linux/reiser_fs.h
 *
 *  Reiser File System constants and structures
 *
 */

/* in reading the #defines, it may help to understand that they employ
   the following abbreviations:

   B = Buffer
   I = Item header
   H = Height within the tree (should be changed to LEV)
   N = Number of the item in the node
   STAT = stat data
   DEH = Directory Entry Header
   EC = Entry Count
   E = Entry number
   UL = Unsigned Long
   BLKH = BLocK Header
   UNFM = UNForMatted node
   DC = Disk Child
   P = Path

   These #defines are named by concatenating these abbreviations,
   where first comes the arguments, and last comes the return value,
   of the macro.

*/

#define USE_INODE_GENERATION_COUNTER

#define REISERFS_PREALLOCATE
#define DISPLACE_NEW_PACKING_LOCALITIES
#define PREALLOCATION_SIZE 9

/* n must be power of 2 */
#define _ROUND_UP(x,n) (((x)+(n)-1u) & ~((n)-1u))

// to be ok for alpha and others we have to align structures to 8 byte
// boundary.
// FIXME: do not change 4 by anything else: there is code which relies on that
#define ROUND_UP(x) _ROUND_UP(x,8LL)

/* debug levels.  Right now, CONFIG_REISERFS_CHECK means print all debug
** messages.
*/
#define REISERFS_DEBUG_CODE 5 /* extra messages to help find/debug errors */ 

void reiserfs_warning (struct super_block *s, const char * fmt, ...);
/* assertions handling */

/** always check a condition and panic if it's false. */
#define RASSERT( cond, format, args... )					\
if( !( cond ) ) 								\
  reiserfs_panic( NULL, "reiserfs[%i]: assertion " #cond " failed at "	\
		  __FILE__ ":%i:%s: " format "\n",		\
		  in_interrupt() ? -1 : current -> pid, __LINE__ , __FUNCTION__ , ##args )

#if defined( CONFIG_REISERFS_CHECK )
#define RFALSE( cond, format, args... ) RASSERT( !( cond ), format, ##args )
#else
#define RFALSE( cond, format, args... ) do {;} while( 0 )
#endif

#define CONSTF __attribute_const__
/*
 * Disk Data Structures
 */

/***************************************************************************/
/*                             SUPER BLOCK                                 */
/***************************************************************************/

/*
 * Structure of super block on disk, a version of which in RAM is often accessed as REISERFS_SB(s)->s_rs
 * the version in RAM is part of a larger structure containing fields never written to disk.
 */
#define UNSET_HASH 0 // read_super will guess about, what hash names
                     // in directories were sorted with
#define TEA_HASH  1
#define YURA_HASH 2
#define R5_HASH   3
#define DEFAULT_HASH R5_HASH


struct journal_params {
    __u32 jp_journal_1st_block;	      /* where does journal start from on its
				       * device */
    __u32 jp_journal_dev;	      /* journal device st_rdev */
    __u32 jp_journal_size;	      /* size of the journal */
    __u32 jp_journal_trans_max;	      /* max number of blocks in a transaction. */
    __u32 jp_journal_magic; 	      /* random value made on fs creation (this
				       * was sb_journal_block_count) */
    __u32 jp_journal_max_batch;	      /* max number of blocks to batch into a
				       * trans */
    __u32 jp_journal_max_commit_age;  /* in seconds, how old can an async
				       * commit be */
    __u32 jp_journal_max_trans_age;   /* in seconds, how old can a transaction
				       * be */
};

/* this is the super from 3.5.X, where X >= 10 */
struct reiserfs_super_block_v1
{
    __u32 s_block_count;	   /* blocks count         */
    __u32 s_free_blocks;           /* free blocks count    */
    __u32 s_root_block;            /* root block number    */
    struct journal_params s_journal;
    __u16 s_blocksize;             /* block size */
    __u16 s_oid_maxsize;	   /* max size of object id array, see
				    * get_objectid() commentary  */
    __u16 s_oid_cursize;	   /* current size of object id array */
    __u16 s_umount_state;          /* this is set to 1 when filesystem was
				    * umounted, to 2 - when not */    
    char s_magic[10];              /* reiserfs magic string indicates that
				    * file system is reiserfs:
				    * "ReIsErFs" or "ReIsEr2Fs" or "ReIsEr3Fs" */
    __u16 s_fs_state;	           /* it is set to used by fsck to mark which
				    * phase of rebuilding is done */
    __u32 s_hash_function_code;    /* indicate, what hash function is being use
				    * to sort names in a directory*/
    __u16 s_tree_height;           /* height of disk tree */
    __u16 s_bmap_nr;               /* amount of bitmap blocks needed to address
				    * each block of file system */
    __u16 s_version;               /* this field is only reliable on filesystem
				    * with non-standard journal */
    __u16 s_reserved_for_journal;  /* size in blocks of journal area on main
				    * device, we need to keep after
				    * making fs with non-standard journal */	
} __attribute__ ((__packed__));

#define SB_SIZE_V1 (sizeof(struct reiserfs_super_block_v1))

/* this is the on disk super block */
struct reiserfs_super_block
{
    struct reiserfs_super_block_v1 s_v1;
    __u32 s_inode_generation;
    __u32 s_flags;                  /* Right now used only by inode-attributes, if enabled */
    unsigned char s_uuid[16];       /* filesystem unique identifier */
    unsigned char s_label[16];      /* filesystem volume label */
    char s_unused[88] ;             /* zero filled by mkreiserfs and
				     * reiserfs_convert_objectid_map_v1()
				     * so any additions must be updated
				     * there as well. */
}  __attribute__ ((__packed__));

#define SB_SIZE (sizeof(struct reiserfs_super_block))

#define REISERFS_VERSION_1 0
#define REISERFS_VERSION_2 2


// on-disk super block fields converted to cpu form
#define SB_DISK_SUPER_BLOCK(s) (REISERFS_SB(s)->s_rs)
#define SB_V1_DISK_SUPER_BLOCK(s) (&(SB_DISK_SUPER_BLOCK(s)->s_v1))
#define SB_BLOCKSIZE(s) \
        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_blocksize))
#define SB_BLOCK_COUNT(s) \
        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_block_count))
#define SB_FREE_BLOCKS(s) \
        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_free_blocks))
#define SB_REISERFS_MAGIC(s) \
        (SB_V1_DISK_SUPER_BLOCK(s)->s_magic)
#define SB_ROOT_BLOCK(s) \
        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_root_block))
#define SB_TREE_HEIGHT(s) \
        le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_tree_height))
#define SB_REISERFS_STATE(s) \
        le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_umount_state))
#define SB_VERSION(s) le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_version))
#define SB_BMAP_NR(s) le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_bmap_nr))

#define PUT_SB_BLOCK_COUNT(s, val) \
   do { SB_V1_DISK_SUPER_BLOCK(s)->s_block_count = cpu_to_le32(val); } while (0)
#define PUT_SB_FREE_BLOCKS(s, val) \
   do { SB_V1_DISK_SUPER_BLOCK(s)->s_free_blocks = cpu_to_le32(val); } while (0)
#define PUT_SB_ROOT_BLOCK(s, val) \
   do { SB_V1_DISK_SUPER_BLOCK(s)->s_root_block = cpu_to_le32(val); } while (0)
#define PUT_SB_TREE_HEIGHT(s, val) \
   do { SB_V1_DISK_SUPER_BLOCK(s)->s_tree_height = cpu_to_le16(val); } while (0)
#define PUT_SB_REISERFS_STATE(s, val) \
   do { SB_V1_DISK_SUPER_BLOCK(s)->s_umount_state = cpu_to_le16(val); } while (0) 
#define PUT_SB_VERSION(s, val) \
   do { SB_V1_DISK_SUPER_BLOCK(s)->s_version = cpu_to_le16(val); } while (0)
#define PUT_SB_BMAP_NR(s, val) \
   do { SB_V1_DISK_SUPER_BLOCK(s)->s_bmap_nr = cpu_to_le16 (val); } while (0)


#define SB_ONDISK_JP(s) (&SB_V1_DISK_SUPER_BLOCK(s)->s_journal)
#define SB_ONDISK_JOURNAL_SIZE(s) \
         le32_to_cpu ((SB_ONDISK_JP(s)->jp_journal_size))
#define SB_ONDISK_JOURNAL_1st_BLOCK(s) \
         le32_to_cpu ((SB_ONDISK_JP(s)->jp_journal_1st_block))
#define SB_ONDISK_JOURNAL_DEVICE(s) \
         le32_to_cpu ((SB_ONDISK_JP(s)->jp_journal_dev))
#define SB_ONDISK_RESERVED_FOR_JOURNAL(s) \
         le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)->s_reserved_for_journal))

#define is_block_in_log_or_reserved_area(s, block) \
         block >= SB_JOURNAL_1st_RESERVED_BLOCK(s) \
         && block < SB_JOURNAL_1st_RESERVED_BLOCK(s) +  \
         ((!is_reiserfs_jr(SB_DISK_SUPER_BLOCK(s)) ? \
         SB_ONDISK_JOURNAL_SIZE(s) + 1 : SB_ONDISK_RESERVED_FOR_JOURNAL(s))) 



				/* used by gcc */
#define REISERFS_SUPER_MAGIC 0x52654973
				/* used by file system utilities that
                                   look at the superblock, etc. */
#define REISERFS_SUPER_MAGIC_STRING "ReIsErFs"
#define REISER2FS_SUPER_MAGIC_STRING "ReIsEr2Fs"
#define REISER2FS_JR_SUPER_MAGIC_STRING "ReIsEr3Fs"

int is_reiserfs_3_5 (struct reiserfs_super_block * rs);
int is_reiserfs_3_6 (struct reiserfs_super_block * rs);
int is_reiserfs_jr (struct reiserfs_super_block * rs);

/* ReiserFS leaves the first 64k unused, so that partition labels have
   enough space.  If someone wants to write a fancy bootloader that
   needs more than 64k, let us know, and this will be increased in size.
   This number must be larger than than the largest block size on any
   platform, or code will break.  -Hans */
#define REISERFS_DISK_OFFSET_IN_BYTES (64 * 1024)
#define REISERFS_FIRST_BLOCK unused_define
#define REISERFS_JOURNAL_OFFSET_IN_BYTES REISERFS_DISK_OFFSET_IN_BYTES

/* the spot for the super in versions 3.5 - 3.5.10 (inclusive) */
#define REISERFS_OLD_DISK_OFFSET_IN_BYTES (8 * 1024)

// reiserfs internal error code (used by search_by_key adn fix_nodes))
#define CARRY_ON      0
#define REPEAT_SEARCH -1
#define IO_ERROR      -2
#define NO_DISK_SPACE -3
#define NO_BALANCING_NEEDED  (-4)
#define NO_MORE_UNUSED_CONTIGUOUS_BLOCKS (-5)
#define QUOTA_EXCEEDED -6

typedef __u32 b_blocknr_t;
typedef __u32 unp_t;

struct unfm_nodeinfo {
    unp_t unfm_nodenum;
    unsigned short unfm_freespace;
};

/* there are two formats of keys: 3.5 and 3.6
 */
#define KEY_FORMAT_3_5 0
#define KEY_FORMAT_3_6 1

/* there are two stat datas */
#define STAT_DATA_V1 0
#define STAT_DATA_V2 1


static inline struct reiserfs_inode_info *REISERFS_I(const struct inode *inode)
{
	return container_of(inode, struct reiserfs_inode_info, vfs_inode);
}

static inline struct reiserfs_sb_info *REISERFS_SB(const struct super_block *sb)
{
	return sb->s_fs_info;
}

/** this says about version of key of all items (but stat data) the
    object consists of */
#define get_inode_item_key_version( inode )                                    \
    ((REISERFS_I(inode)->i_flags & i_item_key_version_mask) ? KEY_FORMAT_3_6 : KEY_FORMAT_3_5)

#define set_inode_item_key_version( inode, version )                           \
         ({ if((version)==KEY_FORMAT_3_6)                                      \
                REISERFS_I(inode)->i_flags |= i_item_key_version_mask;      \
            else                                                               \
                REISERFS_I(inode)->i_flags &= ~i_item_key_version_mask; })

#define get_inode_sd_version(inode)                                            \
    ((REISERFS_I(inode)->i_flags & i_stat_data_version_mask) ? STAT_DATA_V2 : STAT_DATA_V1)

#define set_inode_sd_version(inode, version)                                   \
         ({ if((version)==STAT_DATA_V2)                                        \
                REISERFS_I(inode)->i_flags |= i_stat_data_version_mask;     \
            else                                                               \
                REISERFS_I(inode)->i_flags &= ~i_stat_data_version_mask; })

/* This is an aggressive tail suppression policy, I am hoping it
   improves our benchmarks. The principle behind it is that percentage
   space saving is what matters, not absolute space saving.  This is
   non-intuitive, but it helps to understand it if you consider that the
   cost to access 4 blocks is not much more than the cost to access 1
   block, if you have to do a seek and rotate.  A tail risks a
   non-linear disk access that is significant as a percentage of total
   time cost for a 4 block file and saves an amount of space that is
   less significant as a percentage of space, or so goes the hypothesis.
   -Hans */
#define STORE_TAIL_IN_UNFM_S1(n_file_size,n_tail_size,n_block_size) \
(\
  (!(n_tail_size)) || \
  (((n_tail_size) > MAX_DIRECT_ITEM_LEN(n_block_size)) || \
   ( (n_file_size) >= (n_block_size) * 4 ) || \
   ( ( (n_file_size) >= (n_block_size) * 3 ) && \
     ( (n_tail_size) >=   (MAX_DIRECT_ITEM_LEN(n_block_size))/4) ) || \
   ( ( (n_file_size) >= (n_block_size) * 2 ) && \
     ( (n_tail_size) >=   (MAX_DIRECT_ITEM_LEN(n_block_size))/2) ) || \
   ( ( (n_file_size) >= (n_block_size) ) && \
     ( (n_tail_size) >=   (MAX_DIRECT_ITEM_LEN(n_block_size) * 3)/4) ) ) \
)

/* Another strategy for tails, this one means only create a tail if all the
   file would fit into one DIRECT item.
   Primary intention for this one is to increase performance by decreasing
   seeking.
*/   
#define STORE_TAIL_IN_UNFM_S2(n_file_size,n_tail_size,n_block_size) \
(\
  (!(n_tail_size)) || \
  (((n_file_size) > MAX_DIRECT_ITEM_LEN(n_block_size)) ) \
)



/*
 * values for s_umount_state field
 */
#define REISERFS_VALID_FS    1
#define REISERFS_ERROR_FS    2

//
// there are 5 item types currently
//
#define TYPE_STAT_DATA 0
#define TYPE_INDIRECT 1
#define TYPE_DIRECT 2
#define TYPE_DIRENTRY 3 
#define TYPE_MAXTYPE 3 
#define TYPE_ANY 15 // FIXME: comment is required

/***************************************************************************/
/*                       KEY & ITEM HEAD                                   */
/***************************************************************************/

//
// directories use this key as well as old files
//
struct offset_v1 {
    __u32 k_offset;
    __u32 k_uniqueness;
} __attribute__ ((__packed__));

struct offset_v2 {
#ifdef __LITTLE_ENDIAN
	    /* little endian version */
	    __u64 k_offset:60;
	    __u64 k_type: 4;
#else
	    /* big endian version */
	    __u64 k_type: 4;
	    __u64 k_offset:60;
#endif
} __attribute__ ((__packed__));

#ifndef __LITTLE_ENDIAN
typedef union {
    struct offset_v2 offset_v2;
    __u64 linear;
} __attribute__ ((__packed__)) offset_v2_esafe_overlay;

static inline __u16 offset_v2_k_type( const struct offset_v2 *v2 )
{
    offset_v2_esafe_overlay tmp = *(const offset_v2_esafe_overlay *)v2;
    tmp.linear = le64_to_cpu( tmp.linear );
    return (tmp.offset_v2.k_type <= TYPE_MAXTYPE)?tmp.offset_v2.k_type:TYPE_ANY;
}
 
static inline void set_offset_v2_k_type( struct offset_v2 *v2, int type )
{
    offset_v2_esafe_overlay *tmp = (offset_v2_esafe_overlay *)v2;
    tmp->linear = le64_to_cpu(tmp->linear);
    tmp->offset_v2.k_type = type;
    tmp->linear = cpu_to_le64(tmp->linear);
}
 
static inline loff_t offset_v2_k_offset( const struct offset_v2 *v2 )
{
    offset_v2_esafe_overlay tmp = *(const offset_v2_esafe_overlay *)v2;
    tmp.linear = le64_to_cpu( tmp.linear );
    return tmp.offset_v2.k_offset;
}

static inline void set_offset_v2_k_offset( struct offset_v2 *v2, loff_t offset ){
    offset_v2_esafe_overlay *tmp = (offset_v2_esafe_overlay *)v2;
    tmp->linear = le64_to_cpu(tmp->linear);
    tmp->offset_v2.k_offset = offset;
    tmp->linear = cpu_to_le64(tmp->linear);
}
#else
# define offset_v2_k_type(v2)           ((v2)->k_type)
# define set_offset_v2_k_type(v2,val)   (offset_v2_k_type(v2) = (val))
# define offset_v2_k_offset(v2)         ((v2)->k_offset)
# define set_offset_v2_k_offset(v2,val) (offset_v2_k_offset(v2) = (val))
#endif

/* Key of an item determines its location in the S+tree, and
   is composed of 4 components */
struct reiserfs_key {
    __u32 k_dir_id;    /* packing locality: by default parent
			  directory object id */
    __u32 k_objectid;  /* object identifier */
    union {
	struct offset_v1 k_offset_v1;
	struct offset_v2 k_offset_v2;
    } __attribute__ ((__packed__)) u;
} __attribute__ ((__packed__));


struct cpu_key {
    struct reiserfs_key on_disk_key;
    int version;
    int key_length; /* 3 in all cases but direct2indirect and
		       indirect2direct conversion */
};

/* Our function for comparing keys can compare keys of different
   lengths.  It takes as a parameter the length of the keys it is to
   compare.  These defines are used in determining what is to be passed
   to it as that parameter. */
#define REISERFS_FULL_KEY_LEN     4
#define REISERFS_SHORT_KEY_LEN    2

/* The result of the key compare */
#define FIRST_GREATER 1
#define SECOND_GREATER -1
#define KEYS_IDENTICAL 0
#define KEY_FOUND 1
#define KEY_NOT_FOUND 0

#define KEY_SIZE (sizeof(struct reiserfs_key))
#define SHORT_KEY_SIZE (sizeof (__u32) + sizeof (__u32))

/* return values for search_by_key and clones */
#define ITEM_FOUND 1
#define ITEM_NOT_FOUND 0
#define ENTRY_FOUND 1
#define ENTRY_NOT_FOUND 0
#define DIRECTORY_NOT_FOUND -1
#define REGULAR_FILE_FOUND -2
#define DIRECTORY_FOUND -3
#define BYTE_FOUND 1
#define BYTE_NOT_FOUND 0
#define FILE_NOT_FOUND -1

#define POSITION_FOUND 1
#define POSITION_NOT_FOUND 0

// return values for reiserfs_find_entry and search_by_entry_key
#define NAME_FOUND 1
#define NAME_NOT_FOUND 0
#define GOTO_PREVIOUS_ITEM 2
#define NAME_FOUND_INVISIBLE 3

/*  Everything in the filesystem is stored as a set of items.  The
    item head contains the key of the item, its free space (for
    indirect items) and specifies the location of the item itself
    within the block.  */

struct item_head
{
	/* Everything in the tree is found by searching for it based on
	 * its key.*/
	struct reiserfs_key ih_key;
	union {
		/* The free space in the last unformatted node of an
		   indirect item if this is an indirect item.  This
		   equals 0xFFFF iff this is a direct item or stat data
		   item. Note that the key, not this field, is used to
		   determine the item type, and thus which field this
		   union contains. */
		__u16 ih_free_space_reserved; 
		/* Iff this is a directory item, this field equals the
		   number of directory entries in the directory item. */
		__u16 ih_entry_count; 
	} __attribute__ ((__packed__)) u;
	__u16 ih_item_len;           /* total size of the item body */
	__u16 ih_item_location;      /* an offset to the item body
				      * within the block */
	__u16 ih_version;	     /* 0 for all old items, 2 for new
					ones. Highest bit is set by fsck
					temporary, cleaned after all
					done */
} __attribute__ ((__packed__));
/* size of item header     */
#define IH_SIZE (sizeof(struct item_head))

#define ih_free_space(ih)            le16_to_cpu((ih)->u.ih_free_space_reserved)
#define ih_version(ih)               le16_to_cpu((ih)->ih_version)
#define ih_entry_count(ih)           le16_to_cpu((ih)->u.ih_entry_count)
#define ih_location(ih)              le16_to_cpu((ih)->ih_item_location)
#define ih_item_len(ih)              le16_to_cpu((ih)->ih_item_len)

#define put_ih_free_space(ih, val)   do { (ih)->u.ih_free_space_reserved = cpu_to_le16(val); } while(0)
#define put_ih_version(ih, val)      do { (ih)->ih_version = cpu_to_le16(val); } while (0)
#define put_ih_entry_count(ih, val)  do { (ih)->u.ih_entry_count = cpu_to_le16(val); } while (0)
#define put_ih_location(ih, val)     do { (ih)->ih_item_location = cpu_to_le16(val); } while (0)
#define put_ih_item_len(ih, val)     do { (ih)->ih_item_len = cpu_to_le16(val); } while (0)


#define unreachable_item(ih) (ih_version(ih) & (1 << 15))

#define get_ih_free_space(ih) (ih_version (ih) == KEY_FORMAT_3_6 ? 0 : ih_free_space (ih))
#define set_ih_free_space(ih,val) put_ih_free_space((ih), ((ih_version(ih) == KEY_FORMAT_3_6) ? 0 : (val)))

/* these operate on indirect items, where you've got an array of ints
** at a possibly unaligned location.  These are a noop on ia32
** 
** p is the array of __u32, i is the index into the array, v is the value
** to store there.
*/
#define get_block_num(p, i) le32_to_cpu(get_unaligned((p) + (i)))
#define put_block_num(p, i, v) put_unaligned(cpu_to_le32(v), (p) + (i))

//
// in old version uniqueness field shows key type
//
#define V1_SD_UNIQUENESS 0
#define V1_INDIRECT_UNIQUENESS 0xfffffffe
#define V1_DIRECT_UNIQUENESS 0xffffffff
#define V1_DIRENTRY_UNIQUENESS 500
#define V1_ANY_UNIQUENESS 555 // FIXME: comment is required

//
// here are conversion routines
//
static inline int uniqueness2type (__u32 uniqueness) CONSTF;
static inline int uniqueness2type (__u32 uniqueness)
{
    switch ((int)uniqueness) {
    case V1_SD_UNIQUENESS: return TYPE_STAT_DATA;
    case V1_INDIRECT_UNIQUENESS: return TYPE_INDIRECT;
    case V1_DIRECT_UNIQUENESS: return TYPE_DIRECT;
    case V1_DIRENTRY_UNIQUENESS: return TYPE_DIRENTRY;
    default:
	    reiserfs_warning (NULL, "vs-500: unknown uniqueness %d",
			      uniqueness);
	case V1_ANY_UNIQUENESS:
	    return TYPE_ANY;
    }
}

static inline __u32 type2uniqueness (int type) CONSTF;
static inline __u32 type2uniqueness (int type)
{
    switch (type) {
    case TYPE_STAT_DATA: return V1_SD_UNIQUENESS;
    case TYPE_INDIRECT: return V1_INDIRECT_UNIQUENESS;
    case TYPE_DIRECT: return V1_DIRECT_UNIQUENESS;
    case TYPE_DIRENTRY: return V1_DIRENTRY_UNIQUENESS;
    default:
	    reiserfs_warning (NULL, "vs-501: unknown type %d", type);
	case TYPE_ANY:
	    return V1_ANY_UNIQUENESS;
    }
}

//
// key is pointer to on disk key which is stored in le, result is cpu,
// there is no way to get version of object from key, so, provide
// version to these defines
//
static inline loff_t le_key_k_offset (int version, const struct reiserfs_key * key)
{
    return (version == KEY_FORMAT_3_5) ?
        le32_to_cpu( key->u.k_offset_v1.k_offset ) :
	offset_v2_k_offset( &(key->u.k_offset_v2) );
}

static inline loff_t le_ih_k_offset (const struct item_head * ih)
{
    return le_key_k_offset (ih_version (ih), &(ih->ih_key));
}

static inline loff_t le_key_k_type (int version, const struct reiserfs_key * key)
{
    return (version == KEY_FORMAT_3_5) ?
        uniqueness2type( le32_to_cpu( key->u.k_offset_v1.k_uniqueness)) :
	offset_v2_k_type( &(key->u.k_offset_v2) );
}

static inline loff_t le_ih_k_type (const struct item_head * ih)
{
    return le_key_k_type (ih_version (ih), &(ih->ih_key));
}


static inline void set_le_key_k_offset (int version, struct reiserfs_key * key, loff_t offset)
{
    (version == KEY_FORMAT_3_5) ?
        (void)(key->u.k_offset_v1.k_offset = cpu_to_le32 (offset)) : /* jdm check */
	(void)(set_offset_v2_k_offset( &(key->u.k_offset_v2), offset ));
}


static inline void set_le_ih_k_offset (struct item_head * ih, loff_t offset)
{
    set_le_key_k_offset (ih_version (ih), &(ih->ih_key), offset);
}


static inline void set_le_key_k_type (int version, struct reiserfs_key * key, int type)
{
    (version == KEY_FORMAT_3_5) ?
        (void)(key->u.k_offset_v1.k_uniqueness = cpu_to_le32(type2uniqueness(type))):
	(void)(set_offset_v2_k_type( &(key->u.k_offset_v2), type ));
}
static inline void set_le_ih_k_type (struct item_head * ih, int type)
{
    set_le_key_k_type (ih_version (ih), &(ih->ih_key), type);
}


#define is_direntry_le_key(version,key) (le_key_k_type (version, key) == TYPE_DIRENTRY)
#define is_direct_le_key(version,key) (le_key_k_type (version, key) == TYPE_DIRECT)
#define is_indirect_le_key(version,key) (le_key_k_type (version, key) == TYPE_INDIRECT)
#define is_statdata_le_key(version,key) (le_key_k_type (version, key) == TYPE_STAT_DATA)

//
// item header has version.
//
#define is_direntry_le_ih(ih) is_direntry_le_key (ih_version (ih), &((ih)->ih_key))
#define is_direct_le_ih(ih) is_direct_le_key (ih_version (ih), &((ih)->ih_key))
#define is_indirect_le_ih(ih) is_indirect_le_key (ih_version(ih), &((ih)->ih_key))
#define is_statdata_le_ih(ih) is_statdata_le_key (ih_version (ih), &((ih)->ih_key))



//
// key is pointer to cpu key, result is cpu
//
static inline loff_t cpu_key_k_offset (const struct cpu_key * key)
{
    return (key->version == KEY_FORMAT_3_5) ?
        key->on_disk_key.u.k_offset_v1.k_offset :
	key->on_disk_key.u.k_offset_v2.k_offset;
}

static inline loff_t cpu_key_k_type (const struct cpu_key * key)
{
    return (key->version == KEY_FORMAT_3_5) ?
        uniqueness2type (key->on_disk_key.u.k_offset_v1.k_uniqueness) :
	key->on_disk_key.u.k_offset_v2.k_type;
}

static inline void set_cpu_key_k_offset (struct cpu_key * key, loff_t offset)
{
    (key->version == KEY_FORMAT_3_5) ?
        (key->on_disk_key.u.k_offset_v1.k_offset = offset) :
	(key->on_disk_key.u.k_offset_v2.k_offset = offset);
}


static inline void set_cpu_key_k_type (struct cpu_key * key, int type)
{
    (key->version == KEY_FORMAT_3_5) ?
        (key->on_disk_key.u.k_offset_v1.k_uniqueness = type2uniqueness (type)):
	(key->on_disk_key.u.k_offset_v2.k_type = type);
}


static inline void cpu_key_k_offset_dec (struct cpu_key * key)
{
    if (key->version == KEY_FORMAT_3_5)
	key->on_disk_key.u.k_offset_v1.k_offset --;
    else
	key->on_disk_key.u.k_offset_v2.k_offset --;
}


#define is_direntry_cpu_key(key) (cpu_key_k_type (key) == TYPE_DIRENTRY)
#define is_direct_cpu_key(key) (cpu_key_k_type (key) == TYPE_DIRECT)
#define is_indirect_cpu_key(key) (cpu_key_k_type (key) == TYPE_INDIRECT)
#define is_statdata_cpu_key(key) (cpu_key_k_type (key) == TYPE_STAT_DATA)


/* are these used ? */
#define is_direntry_cpu_ih(ih) (is_direntry_cpu_key (&((ih)->ih_key)))
#define is_direct_cpu_ih(ih) (is_direct_cpu_key (&((ih)->ih_key)))
#define is_indirect_cpu_ih(ih) (is_indirect_cpu_key (&((ih)->ih_key)))
#define is_statdata_cpu_ih(ih) (is_statdata_cpu_key (&((ih)->ih_key)))





#define I_K_KEY_IN_ITEM(p_s_ih, p_s_key, n_blocksize) \
    ( ! COMP_SHORT_KEYS(p_s_ih, p_s_key) && \
          I_OFF_BYTE_IN_ITEM(p_s_ih, k_offset (p_s_key), n_blocksize) )

/* maximal length of item */ 
#define MAX_ITEM_LEN(block_size) (block_size - BLKH_SIZE - IH_SIZE)
#define MIN_ITEM_LEN 1


/* object identifier for root dir */
#define REISERFS_ROOT_OBJECTID 2
#define REISERFS_ROOT_PARENT_OBJECTID 1
extern struct reiserfs_key root_key;




/* 
 * Picture represents a leaf of the S+tree
 *  ______________________________________________________
 * |      |  Array of     |                   |           |
 * |Block |  Object-Item  |      F r e e      |  Objects- |
 * | head |  Headers      |     S p a c e     |   Items   |
 * |______|_______________|___________________|___________|
 */

/* Header of a disk block.  More precisely, header of a formatted leaf
   or internal node, and not the header of an unformatted node. */
struct block_head {       
  __u16 blk_level;        /* Level of a block in the tree. */
  __u16 blk_nr_item;      /* Number of keys/items in a block. */
  __u16 blk_free_space;   /* Block free space in bytes. */
  __u16 blk_reserved;
				/* dump this in v4/planA */
  struct reiserfs_key  blk_right_delim_key; /* kept only for compatibility */
};

#define BLKH_SIZE                     (sizeof(struct block_head))
#define blkh_level(p_blkh)            (le16_to_cpu((p_blkh)->blk_level))
#define blkh_nr_item(p_blkh)          (le16_to_cpu((p_blkh)->blk_nr_item))
#define blkh_free_space(p_blkh)       (le16_to_cpu((p_blkh)->blk_free_space))
#define blkh_reserved(p_blkh)         (le16_to_cpu((p_blkh)->blk_reserved))
#define set_blkh_level(p_blkh,val)    ((p_blkh)->blk_level = cpu_to_le16(val))
#define set_blkh_nr_item(p_blkh,val)  ((p_blkh)->blk_nr_item = cpu_to_le16(val))
#define set_blkh_free_space(p_blkh,val) ((p_blkh)->blk_free_space = cpu_to_le16(val))
#define set_blkh_reserved(p_blkh,val) ((p_blkh)->blk_reserved = cpu_to_le16(val))
#define blkh_right_delim_key(p_blkh)  ((p_blkh)->blk_right_delim_key)
#define set_blkh_right_delim_key(p_blkh,val)  ((p_blkh)->blk_right_delim_key = val)

/*
 * values for blk_level field of the struct block_head
 */

#define FREE_LEVEL 0 /* when node gets removed from the tree its
			blk_level is set to FREE_LEVEL. It is then
			used to see whether the node is still in the
			tree */

#define DISK_LEAF_NODE_LEVEL  1 /* Leaf node level.*/

/* Given the buffer head of a formatted node, resolve to the block head of that node. */
#define B_BLK_HEAD(p_s_bh)            ((struct block_head *)((p_s_bh)->b_data))
/* Number of items that are in buffer. */
#define B_NR_ITEMS(p_s_bh)            (blkh_nr_item(B_BLK_HEAD(p_s_bh)))
#define B_LEVEL(p_s_bh)               (blkh_level(B_BLK_HEAD(p_s_bh)))
#define B_FREE_SPACE(p_s_bh)          (blkh_free_space(B_BLK_HEAD(p_s_bh)))

#define PUT_B_NR_ITEMS(p_s_bh,val)    do { set_blkh_nr_item(B_BLK_HEAD(p_s_bh),val); } while (0)
#define PUT_B_LEVEL(p_s_bh,val)       do { set_blkh_level(B_BLK_HEAD(p_s_bh),val); } while (0)
#define PUT_B_FREE_SPACE(p_s_bh,val)  do { set_blkh_free_space(B_BLK_HEAD(p_s_bh),val); } while (0)


/* Get right delimiting key. -- little endian */
#define B_PRIGHT_DELIM_KEY(p_s_bh)   (&(blk_right_delim_key(B_BLK_HEAD(p_s_bh))

/* Does the buffer contain a disk leaf. */
#define B_IS_ITEMS_LEVEL(p_s_bh)     (B_LEVEL(p_s_bh) == DISK_LEAF_NODE_LEVEL)

/* Does the buffer contain a disk internal node */
#define B_IS_KEYS_LEVEL(p_s_bh)      (B_LEVEL(p_s_bh) > DISK_LEAF_NODE_LEVEL \
                                            && B_LEVEL(p_s_bh) <= MAX_HEIGHT)




/***************************************************************************/
/*                             STAT DATA                                   */
/***************************************************************************/


//
// old stat data is 32 bytes long. We are going to distinguish new one by
// different size
//
struct stat_data_v1
{
    __u16 sd_mode;	/* file type, permissions */
    __u16 sd_nlink;	/* number of hard links */
    __u16 sd_uid;		/* owner */
    __u16 sd_gid;		/* group */
    __u32 sd_size;	/* file size */
    __u32 sd_atime;	/* time of last access */
    __u32 sd_mtime;	/* time file was last modified  */
    __u32 sd_ctime;	/* time inode (stat data) was last changed (except changes to sd_atime and sd_mtime) */
    union {
	__u32 sd_rdev;
	__u32 sd_blocks;	/* number of blocks file uses */
    } __attribute__ ((__packed__)) u;
    __u32 sd_first_direct_byte; /* first byte of file which is stored
				   in a direct item: except that if it
				   equals 1 it is a symlink and if it
				   equals ~(__u32)0 there is no
				   direct item.  The existence of this
				   field really grates on me. Let's
				   replace it with a macro based on
				   sd_size and our tail suppression
				   policy.  Someday.  -Hans */
} __attribute__ ((__packed__));

#define SD_V1_SIZE              (sizeof(struct stat_data_v1))
#define stat_data_v1(ih)        (ih_version (ih) == KEY_FORMAT_3_5)
#define sd_v1_mode(sdp)         (le16_to_cpu((sdp)->sd_mode))
#define set_sd_v1_mode(sdp,v)   ((sdp)->sd_mode = cpu_to_le16(v))
#define sd_v1_nlink(sdp)        (le16_to_cpu((sdp)->sd_nlink))
#define set_sd_v1_nlink(sdp,v)  ((sdp)->sd_nlink = cpu_to_le16(v))
#define sd_v1_uid(sdp)          (le16_to_cpu((sdp)->sd_uid))
#define set_sd_v1_uid(sdp,v)    ((sdp)->sd_uid = cpu_to_le16(v))
#define sd_v1_gid(sdp)          (le16_to_cpu((sdp)->sd_gid))
#define set_sd_v1_gid(sdp,v)    ((sdp)->sd_gid = cpu_to_le16(v))
#define sd_v1_size(sdp)         (le32_to_cpu((sdp)->sd_size))
#define set_sd_v1_size(sdp,v)   ((sdp)->sd_size = cpu_to_le32(v))
#define sd_v1_atime(sdp)        (le32_to_cpu((sdp)->sd_atime))
#define set_sd_v1_atime(sdp,v)  ((sdp)->sd_atime = cpu_to_le32(v))
#define sd_v1_mtime(sdp)        (le32_to_cpu((sdp)->sd_mtime))
#define set_sd_v1_mtime(sdp,v)  ((sdp)->sd_mtime = cpu_to_le32(v))
#define sd_v1_ctime(sdp)        (le32_to_cpu((sdp)->sd_ctime))
#define set_sd_v1_ctime(sdp,v)  ((sdp)->sd_ctime = cpu_to_le32(v))
#define sd_v1_rdev(sdp)         (le32_to_cpu((sdp)->u.sd_rdev))
#define set_sd_v1_rdev(sdp,v)   ((sdp)->u.sd_rdev = cpu_to_le32(v))
#define sd_v1_blocks(sdp)       (le32_to_cpu((sdp)->u.sd_blocks))
#define set_sd_v1_blocks(sdp,v) ((sdp)->u.sd_blocks = cpu_to_le32(v))
#define sd_v1_first_direct_byte(sdp) \
                                (le32_to_cpu((sdp)->sd_first_direct_byte))
#define set_sd_v1_first_direct_byte(sdp,v) \
                                ((sdp)->sd_first_direct_byte = cpu_to_le32(v))

#include <linux/ext2_fs.h>