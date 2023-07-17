/*
 * Linux Security plug
 *
 * Copyright (C) 2001 WireX Communications, Inc <chris@wirex.com>
 * Copyright (C) 2001 Greg Kroah-Hartman <greg@kroah.com>
 * Copyright (C) 2001 Networks Associates Technology, Inc <ssmalley@nai.com>
 * Copyright (C) 2001 James Morris <jmorris@intercode.com.au>
 * Copyright (C) 2001 Silicon Graphics, Inc. (Trust Technology Group)
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	Due to this file being licensed under the GPL there is controversy over
 *	whether this permits you to write a module that #includes this file
 *	without placing your module under the GPL.  Please consult a lawyer for
 *	advice before doing this.
 *
 */

#ifndef __LINUX_SECURITY_H
#define __LINUX_SECURITY_H

#include <linux/fs.h>
#include <linux/binfmts.h>
#include <linux/signal.h>
#include <linux/resource.h>
#include <linux/sem.h>
#include <linux/shm.h>
#include <linux/msg.h>
#include <linux/sched.h>

struct ctl_table;

/*
 * These functions are in security/capability.c and are used
 * as the default capabilities functions
 */
extern int cap_capable (struct task_struct *tsk, int cap);
extern int cap_settime (struct timespec *ts, struct timezone *tz);
extern int cap_ptrace (struct task_struct *parent, struct task_struct *child);
extern int cap_capget (struct task_struct *target, kernel_cap_t *effective, kernel_cap_t *inheritable, kernel_cap_t *permitted);
extern int cap_capset_check (struct task_struct *target, kernel_cap_t *effective, kernel_cap_t *inheritable, kernel_cap_t *permitted);
extern void cap_capset_set (struct task_struct *target, kernel_cap_t *effective, kernel_cap_t *inheritable, kernel_cap_t *permitted);
extern int cap_bprm_set_security (struct linux_binprm *bprm);
extern void cap_bprm_apply_creds (struct linux_binprm *bprm, int unsafe);
extern int cap_bprm_secureexec(struct linux_binprm *bprm);
extern int cap_inode_setxattr(struct dentry *dentry, char *name, void *value, size_t size, int flags);
extern int cap_inode_removexattr(struct dentry *dentry, char *name);
extern int cap_task_post_setuid (uid_t old_ruid, uid_t old_euid, uid_t old_suid, int flags);
extern void cap_task_reparent_to_init (struct task_struct *p);
extern int cap_syslog (int type);
extern int cap_vm_enough_memory (long pages);

struct msghdr;
struct sk_buff;
struct sock;
struct sockaddr;
struct socket;

extern int cap_netlink_send(struct sock *sk, struct sk_buff *skb);
extern int cap_netlink_recv(struct sk_buff *skb);

/*
 * Values used in the task_security_ops calls
 */
/* setuid or setgid, id0 == uid or gid */
#define LSM_SETID_ID	1

/* setreuid or setregid, id0 == real, id1 == eff */
#define LSM_SETID_RE	2

/* setresuid or setresgid, id0 == real, id1 == eff, uid2 == saved */
#define LSM_SETID_RES	4

/* setfsuid or setfsgid, id0 == fsuid or fsgid */
#define LSM_SETID_FS	8

/* forward declares to avoid warnings */
struct nfsctl_arg;
struct sched_param;
struct swap_info_struct;

/* bprm_apply_creds unsafe reasons */
#define LSM_UNSAFE_SHARE	1
#define LSM_UNSAFE_PTRACE	2
#define LSM_UNSAFE_PTRACE_CAP	4

#ifdef CONFIG_SECURITY

/**
 * struct security_operations - main security structure
 *
 * Security hooks for program execution operations.
 *
 * @bprm_alloc_security:
 *	Allocate and attach a security structure to the @bprm->security field.
 *	The security field is initialized to NULL when the bprm structure is
 *	allocated.
 *	@bprm contains the linux_binprm structure to be modified.
 *	Return 0 if operation was successful.
 * @bprm_free_security:
 *	@bprm contains the linux_binprm structure to be modified.
 *	Deallocate and clear the @bprm->security field.
 * @bprm_apply_creds:
 *	Compute and set the security attributes of a process being transformed
 *	by an execve operation based on the old attributes (current->security)
 *	and the information saved in @bprm->security by the set_security hook.
 *	Since this hook function (and its caller) are void, this hook can not
 *	return an error.  However, it can leave the security attributes of the
 *	process unchanged if an access failure occurs at this point.
 *	bprm_apply_creds is called under task_lock.  @unsafe indicates various
 *	reasons why it may be unsafe to change security state.
 *	@bprm contains the linux_binprm structure.
 * @bprm_post_apply_creds:
 *	Runs after bprm_apply_creds with the task_lock dropped, so that
 *	functions which cannot be called safely under the task_lock can
 *	be used.  This hook is a good place to perform state changes on
 *	the process such as closing open file descriptors to which access
 *	is no longer granted if the attributes were changed.
 *	Note that a security module might need to save state between
 *	bprm_apply_creds and bprm_post_apply_creds to store the decision
 *	on whether the process may proceed.
 *	@bprm contains the linux_binprm structure.
 * @bprm_set_security:
 *	Save security information in the bprm->security field, typically based
 *	on information about the bprm->file, for later use by the apply_creds
 *	hook.  This hook may also optionally check permissions (e.g. for
 *	transitions between security domains).
 *	This hook may be called multiple times during a single execve, e.g. for
 *	interpreters.  The hook can tell whether it has already been called by
 *	checking to see if @bprm->security is non-NULL.  If so, then the hook
 *	may decide either to retain the security information saved earlier or
 *	to replace it.
 *	@bprm contains the linux_binprm structure.
 *	Return 0 if the hook is successful and permission is granted.
 * @bprm_check_security:
 * 	This hook mediates the point when a search for a binary handler	will
 * 	begin.  It allows a check the @bprm->security value which is set in
 * 	the preceding set_security call.  The primary difference from
 * 	set_security is that the argv list and envp list are reliably
 * 	available in @bprm.  This hook may be called multiple times
 * 	during a single execve; and in each pass set_security is called
 * 	first.
 * 	@bprm contains the linux_binprm structure.
 *	Return 0 if the hook is successful and permission is granted.
 * @bprm_secureexec:
 *      Return a boolean value (0 or 1) indicating whether a "secure exec" 
 *      is required.  The flag is passed in the auxiliary table
 *      on the initial stack to the ELF interpreter to indicate whether libc 
 *      should enable secure mode.
 *      @bprm contains the linux_binprm structure.
 *
 * Security hooks for filesystem operations.
 *
 * @sb_alloc_security:
 *	Allocate and attach a security structure to the sb->s_security field.
 *	The s_security field is initialized to NULL when the structure is
 *	allocated.
 *	@sb contains the super_block structure to be modified.
 *	Return 0 if operation was successful.
 * @sb_free_security:
 *	Deallocate and clear the sb->s_security field.
 *	@sb contains the super_block structure to be modified.
 * @sb_statfs:
 *	Check permission before obtaining filesystem statistics for the @sb
 *	filesystem.
 *	@sb contains the super_block structure for the filesystem.
 *	Return 0 if permission is granted.  
 * @sb_mount:
 *	Check permission before an object specified by @dev_name is mounted on
 *	the mount point named by @nd.  For an ordinary mount, @dev_name
 *	identifies a device if the file system type requires a device.  For a
 *	remount (@flags & MS_REMOUNT), @dev_name is irrelevant.  For a
 *	loopback/bind mount (@flags & MS_BIND), @dev_name identifies the
 *	pathname of the object being mounted.
 *	@dev_name contains the name for object being mounted.
 *	@nd contains the nameidata structure for mount point object.
 *	@type contains the filesystem type.
 *	@flags contains the mount flags.
 *	@data contains the filesystem-specific data.
 *	Return 0 if permission is granted.
 * @sb_copy_data:
 *	Allow mount option data to be copied prior to parsing by the filesystem,
 *	so that the security module can extract security-specific mount
 *	options cleanly (a filesystem may modify the data e.g. with strsep()).
 *	This also allows the original mount data to be stripped of security-
 *	specific options to avoid having to make filesystems aware of them.
 *	@type the type of filesystem being mounted.
 *	@orig the original mount data copied from userspace.
 *	@copy copied data which will be passed to the security module.
 *	Returns 0 if the copy was successful.
 * @sb_check_sb:
 *	Check permission before the device with superblock @mnt->sb is mounted
 *	on the mount point named by @nd.
 *	@mnt contains the vfsmount for device being mounted.
 *	@nd contains the nameidata object for the mount point.
 *	Return 0 if permission is granted.
 * @sb_umount:
 *	Check permission before the @mnt file system is unmounted.
 *	@mnt contains the mounted file system.
 *	@flags contains the unmount flags, e.g. MNT_FORCE.
 *	Return 0 if permission is granted.
 * @sb_umount_close:
 *	Close any files in the @mnt mounted filesystem that are held open by
 *	the security module.  This hook is called during an umount operation
 *	prior to checking whether the filesystem is still busy.
 *	@mnt contains the mounted filesystem.
 * @sb_umount_busy:
 *	Handle a failed umount of the @mnt mounted filesystem, e.g.  re-opening
 *	any files that were closed by umount_close.  This hook is called during
 *	an umount operation if the umount fails after a call to the
 *	umount_close hook.
 *	@mnt contains the mounted filesystem.
 * @sb_post_remount:
 *	Update the security module's state when a filesystem is remounted.
 *	This hook is only called if the remount was successful.
 *	@mnt contains the mounted file system.
 *	@flags contains the new filesystem flags.
 *	@data contains the filesystem-specific data.
 * @sb_post_mountroot:
 *	Update the security module's state when the root filesystem is mounted.
 *	This hook is only called if the mount was successful.
 * @sb_post_addmount:
 *	Update the security module's state when a filesystem is mounted.
 *	This hook is called any time a mount is successfully grafetd to
 *	the tree.
 *	@mnt contains the mounted filesystem.
 *	@mountpoint_nd contains the nameidata structure for the mount point.
 * @sb_pivotroot:
 *	Check permission before pivoting the root filesystem.
 *	@old_nd contains the nameidata structure for the new location of the current root (put_old).
 *      @new_nd contains the nameidata structure for the new root (new_root).
 *	Return 0 if permission is granted.
 * @sb_post_pivotroot:
 *	Update module state after a successful pivot.
 *	@old_nd contains the nameidata structure for the old root.
 *      @new_nd contains the nameidata structure for the new root.
 *
 * Security hooks for inode operations.
 *
 * @inode_alloc_security:
 *	Allocate and attach a security structure to @inode->i_security.  The
 *	i_security field is initialized to NULL when the inode structure is
 *	allocated.
 *	@inode contains the inode structure.
 *	Return 0 if operation was successful.
 * @inode_free_security:
 *	@inode contains the inode structure.
 *	Deallocate the inode security structure and set @inode->i_security to
 *	NULL. 
 * @inode_create:
 *	Check permission to create a regular file.
 *	@dir contains inode structure of the parent of the new file.
 *	@dentry contains the dentry structure for the file to be created.
 *	@mode contains the file mode of the file to be created.
 *	Return 0 if permission is granted.
 * @inode_post_create:
 *	Set the security attributes on a newly created regular file.  This hook
 *	is called after a file has been successfully created.
 *	@dir contains the inode structure of the parent directory of the new file.
 *	@dentry contains the the dentry structure for the newly created file.
 *	@mode contains the file mode.
 * @inode_link:
 *	Check permission before creating a new hard link to a file.
 *	@old_dentry contains the dentry structure for an existing link to the file.
 *	@dir contains the inode structure of the parent directory of the new link.
 *	@new_dentry contains the dentry structure for the new link.
 *	Return 0 if permission is granted.
 * @inode_post_link:
 *	Set security attributes for a new hard link to a file.
 *	@old_dentry contains the dentry structure for the existing link.
 *	@dir contains the inode structure of the parent directory of the new file.
 *	@new_dentry contains the dentry structure for the new file link.
 * @inode_unlink:
 *	Check the permission to remove a hard link to a file. 
 *	@dir contains the inode structure of parent directory of the file.
 *	@dentry contains the dentry structure for file to be unlinked.
 *	Return 0 if permission is granted.
 * @inode_symlink:
 *	Check the permission to create a symbolic link to a file.
 *	@dir contains the inode structure of parent directory of the symbolic link.
 *	@dentry contains the dentry structure of the symbolic link.
 *	@old_name contains the pathname of file.
 *	Return 0 if permission is granted.
 * @inode_post_symlink:
 *	@dir contains the inode structure of the parent directory of the new link.
 *	@dentry contains the dentry structure of new symbolic link.
 *	@old_name contains the pathname of file.
 *	Set security attributes for a newly created symbolic link.  Note that
 *	@dentry->d_inode may be NULL, since the filesystem might not
 *	instantiate the dentry (e.g. NFS).
 * @inode_mkdir:
 *	Check permissions to create a new directory in the existing directory
 *	associated with inode strcture @dir. 
 *	@dir containst the inode structure of parent of the directory to be created.
 *	@dentry contains the dentry structure of new directory.
 *	@mode contains the mode of new directory.
 *	Return 0 if permission is granted.
 * @inode_post_mkdir:
 *	Set security attributes on a newly created directory.
 *	@dir contains the inode structure of parent of the directory to be created.
 *	@dentry contains the dentry structure of new directory.
 *	@mode contains the mode of new directory.
 * @inode_rmdir:
 *	Check the permission to remove a directory.
 *	@dir contains the inode structure of parent of the directory to be removed.
 *	@dentry contains the dentry structure of directory to be removed.
 *	Return 0 if permission is granted.
 * @inode_mknod:
 *	Check permissions when creating a special file (or a socket or a fifo
 *	file created via the mknod system call).  Note that if mknod operation
 *	is being done for a regular file, then the create hook will be called
 *	and not this hook.
 *	@dir contains the inode structure of parent of the new file.
 *	@dentry contains the dentry structure of the new file.
 *	@mode contains the mode of the new file.
 *	@dev contains the the device number.
 *	Return 0 if permission is granted.
 * @inode_post_mknod:
 *	Set security attributes on a newly created special file (or socket or
 *	fifo file created via the mknod system call).
 *	@dir contains the inode structure of parent of the new node.
 *	@dentry contains the dentry structure of the new node.
 *	@mode contains the mode of the new node.
 *	@dev contains the the device number.
 * @inode_rename:
 *	Check for permission to rename a file or directory.
 *	@old_dir contains the inode structure for parent of the old link.
 *	@old_dentry contains the dentry structure of the old link.
 *	@new_dir contains the inode structure for parent of the new link.
 *	@new_dentry contains the dentry structure of the new link.
 *	Return 0 if permission is granted.
 * @inode_post_rename:
 *	Set security attributes on a renamed file or directory.
 *	@old_dir contains the inode structure for parent of the old link.
 *	@old_dentry contains the dentry structure of the old link.
 *	@new_dir contains the inode structure for parent of the new link.
 *	@new_dentry contains the dentry structure of the new link.
 * @inode_readlink:
 *	Check the permission to read the symbolic link.
 *	@dentry contains the dentry structure for the file link.
 *	Return 0 if permission is granted.
 * @inode_follow_link:
 *	Check permission to follow a symbolic link when looking up a pathname.
 *	@dentry contains the dentry structure for the link.
 *	@nd contains the nameidata structure for the parent directory.
 *	Return 0 if permission is granted.
 * @inode_permission:
 *	Check permission before accessing an inode.  This hook is called by the
 *	existing Linux permission function, so a security module can use it to
 *	provide additional checking for existing Linux permission checks.
 *	Notice that this hook is called when a file is opened (as well as many
 *	other operations), whereas the file_security_ops permission hook is
 *	called when the actual read/write operations are performed.
 *	@inode contains the inode structure to check.
 *	@mask contains the permission mask.
 *     @nd contains the nameidata (may be NULL).
 *	Return 0 if permission is granted.
 * @inode_setattr:
 *	Check permission before setting file attributes.  Note that the kernel
 *	call to notify_change is performed from several locations, whenever
 *	file attributes change (such as when a file is truncated, chown/chmod
 *	operations, transferring disk quotas, etc).
 *	@dentry contains the dentry structure for the file.
 *	@attr is the iattr structure containing the new file attributes.
 *	Return 0 if permission is granted.
 * @inode_getattr:
 *	Check permission before obtaining file attributes.
 *	@mnt is the vfsmount where the dentry was looked up
 *	@dentry contains the dentry structure for the file.
 *	Return 0 if permission is granted.
 * @inode_delete:
 *	@inode contains the inode structure for deleted inode.
 *	This hook is called when a deleted inode is released (i.e. an inode
 *	with no hard links has its use count drop to zero).  A security module
 *	can use this hook to release any persistent label associated with the
 *	inode.
 * @inode_setxattr:
 * 	Check permission before setting the extended attributes
 * 	@value identified by @name for @dentry.
 * 	Return 0 if permission is granted.
 * @inode_post_setxattr:
 * 	Update inode security field after successful setxattr operation.
 * 	@value identified by @name for @dentry.
 * @inode_getxattr:
 * 	Check permission before obtaining the extended attributes
 * 	identified by @name for @dentry.
 * 	Return 0 if permission is granted.
 * @inode_listxattr:
 * 	Check permission before obtaining the list of extended attribute 
 * 	names for @dentry.
 * 	Return 0 if permission is granted.
 * @inode_removexattr:
 * 	Check permission before removing the extended attribute
 * 	identified by @name for @dentry.
 * 	Return 0 if permission is granted.
 * @inode_getsecurity:
 *	Copy the extended attribute representation of the security label 
 *	associated with @name for @inode into @buffer.  @buffer may be
 *	NULL to request the size of the buffer required.  @size indicates
 *	the size of @buffer in bytes.  Note that @name is the remainder
 *	of the attribute name after the security. prefix has been removed.
 *	Return number of bytes used/required on success.
 * @inode_setsecurity:
 *	Set the security label associated with @name for @inode from the
 *	extended attribute value @value.  @size indicates the size of the
 *	@value in bytes.  @flags may be XATTR_CREATE, XATTR_REPLACE, or 0.
 *	Note that @name is the remainder of the attribute name after the 
 *	security. prefix has been removed.
 *	Return 0 on success.
 * @inode_listsecurity:
 *	Copy the extended attribute names for the security labels
 *	associated with @inode into @buffer.  The maximum size of @buffer
 *	is specified by @buffer_size.  @buffer may be NULL to request
 *	the size of the buffer required.
 *	Returns number of bytes used/required on success.
 *
 * Security hooks for file operations
 *
 * @file_permission:
 *	Check file permissions before accessing an open file.  This hook is
 *	called by various operations that read or write files.  A security
 *	module can use this hook to perform additional checking on these
 *	operations, e.g.  to revalidate permissions on use to support privilege
 *	bracketing or policy changes.  Notice that this hook is used when the
 *	actual read/write operations are performed, whereas the
 *	inode_security_ops hook is called when a file is opened (as well as
 *	many other operations).
 *	Caveat:  Although this hook can be used to revalidate permissions for
 *	various system call operations that read or write files, it does not
 *	address the revalidation of permissions for memory-mapped files.
 *	Security modules must handle this separately if they need such
 *	revalidation.
 *	@file contains the file structure being accessed.
 *	@mask contains the requested permissions.
 *	Return 0 if permission is granted.
 * @file_alloc_security:
 *	Allocate and attach a security structure to the file->f_security field.
 *	The security field is initialized to NULL when the structure is first
 *	created.
 *	@file contains the file structure to secure.
 *	Return 0 if the hook is successful and permission is granted.
 * @file_free_security:
 *	Deallocate and free any security structures stored in file->f_security.
 *	@file contains the file structure being modified.
 * @file_ioctl:
 *	@file contains the file structure.
 *	@cmd contains the operation to perform.
 *	@arg contains the operational arguments.
 *	Check permission for an ioctl operation on @file.  Note that @arg can
 *	sometimes represents a user space pointer; in other cases, it may be a
 *	simple integer value.  When @arg represents a user space pointer, it
 *	should never be used by the security module.
 *	Return 0 if permission is granted.
 * @file_mmap :
 *	Check permissions for a mmap operation.  The @file may be NULL, e.g.
 *	if mapping anonymous memory.
 *	@file contains the file structure for file to map (may be NULL).
 *	@prot contains the requested permissions.
 *	@flags contains the operational flags.
 *	Return 0 if permission is granted.
 * @file_mprotect:
 *	Check permissions before changing memory access permissions.
 *	@vma contains the memory region to modify.
 *	@prot contains the requested permissions.
 *	Return 0 if permission is granted.
 * @file_lock:
 *	Check permission before performing file locking operations.
 *	Note: this hook mediates both flock and fcntl style locks.
 *	@file contains the file structure.
 *	@cmd contains the posix-translated lock operation to perform
 *	(e.g. F_RDLCK, F_WRLCK).
 *	Return 0 if permission is granted.
 * @file_fcntl:
 *	Check permission before allowing the file operation specified by @cmd
 *	from being performed on the file @file.  Note that @arg can sometimes
 *	represents a user space pointer; in other cases, it may be a simple
 *	integer value.  When @arg represents a user space pointer, it should
 *	never be used by the security module.
 *	@file contains the file structure.
 *	@cmd contains the operation to be performed.
 *	@arg contains the operational arguments.
 *	Return 0 if permission is granted.
 * @file_set_fowner:
 *	Save owner security information (typically from current->security) in
 *	file->f_security for later use by the send_sigiotask hook.
 *	@file contains the file structure to update.
 *	Return 0 on success.
 * @file_send_sigiotask:
 *	Check permission for the file owner @fown to send SIGIO or SIGURG to the
 *	process @tsk.  Note that this hook is sometimes called from interrupt.
 *	Note that the fown_struct, @fown, is never outside the context of a
 *	struct file, so the file structure (and associated security information)
 *	can always be obtained:
 *		(struct file *)((long)fown - offsetof(struct file,f_owner));
 * 	@tsk contains the structure of task receiving signal.
 *	@fown contains the file owner information.
 *	@sig is the signal that will be sent.  When 0, kernel sends SIGIO.
 *	Return 0 if permission is granted.
 * @file_receive:
 *	This hook allows security modules to control the ability of a process
 *	to receive an open file descriptor via socket IPC.
 *	@file contains the file structure being received.
 *	Return 0 if permission is granted.
 *
 * Security hooks for task operations.
 *
 * @task_create:
 *	Check permission before creating a child process.  See the clone(2)
 *	manual page for definitions of the @clone_flags.
 *	@clone_flags contains the flags indicating what should be shared.
 *	Return 0 if permission is granted.
 * @task_alloc_security:
 *	@p contains the task_struct for child process.
 *	Allocate and attach a security structure to the p->security field. The
 *	security field is initialized to NULL when the task structure is
 *	allocated.
 *	Return 0 if operation was successful.
 * @task_free_security:
 *	@p contains the task_struct for process.
 *	Deallocate and clear the p->security field.
 * @task_setuid:
 *	Check permission before setting one or more of the user identity
 *	attributes of the current process.  The @flags parameter indicates
 *	which of the set*uid system calls invoked this hook and how to
 *	interpret the @id0, @id1, and @id2 parameters.  See the LSM_SETID
 *	definitions at the beginning of this file for the @flags values and
 *	their meanings.
 *	@id0 contains a uid.
 *	@id1 contains a uid.
 *	@id2 contains a uid.
 *	@flags contains one of the LSM_SETID_* values.
 *	Return 0 if permission is granted.
 * @task_post_setuid:
 *	Update the module's state after setting one or more of the user
 *	identity attributes of the current process.  The @flags parameter
 *	indicates which of the set*uid system calls invoked this hook.  If
 *	@flags is LSM_SETID_FS, then @old_ruid is the old fs uid and the other
 *	parameters are not used.
 *	@old_ruid contains the old real uid (or fs uid if LSM_SETID_FS).
 *	@old_euid contains the old effective uid (or -1 if LSM_SETID_FS).
 *	@old_suid contains the old saved uid (or -1 if LSM_SETID_FS).
 *	@flags contains one of the LSM_SETID_* values.
 *	Return 0 on success.
 * @task_setgid:
 *	Check permission before setting one or more of the group identity
 *	attributes of the current process.  The @flags parameter indicates
 *	which of the set*gid system calls invoked this hook and how to
 *	interpret the @id0, @id1, and @id2 parameters.  See the LSM_SETID
 *	definitions at the beginning of this file for the @flags values and
 *	their meanings.
 *	@id0 contains a gid.
 *	@id1 contains a gid.
 *	@id2 contains a gid.
 *	@flags contains one of the LSM_SETID_* values.
 *	Return 0 if permission is granted.
 * @task_setpgid:
 *	Check permission before setting the process group identifier of the
 *	process @p to @pgid.
 *	@p contains the task_struct for process being modified.
 *	@pgid contains the new pgid.
 *	Return 0 if permission is granted.
 * @task_getpgid:
 *	Check permission before getting the process group identifier of the
 *	process @p.
 *	@p contains the task_struct for the process.
 *	Return 0 if permission is granted.
 * @task_getsid:
 *	Check permission before getting the session identifier of the process
 *	@p.
 *	@p contains the task_struct for the process.
 *	Return 0 if permission is granted.
 * @task_setgroups:
 *	Check permission before setting the supplementary group set of the
 *	current process.
 *	@group_info contains the new group information.
 *	Return 0 if permission is granted.
 * @task_setnice:
 *	Check permission before setting the nice value of @p to @nice.
 *	@p contains the task_struct of process.
 *	@nice contains the new nice value.
 *	Return 0 if permission is granted.
 * @task_setrlimit:
 *	Check permission before setting the resource limits of the current
 *	process for @resource to @new_rlim.  The old resource limit values can
 *	be examined by dereferencing (current->signal->rlim + resource).
 *	@resource contains the resource whose limit is being set.
 *	@new_rlim contains the new limits for @resource.
 *	Return 0 if permission is granted.
 * @task_setscheduler:
 *	Check permission before setting scheduling policy and/or parameters of
 *	process @p based on @policy and @lp.
 *	@p contains the task_struct for process.
 *	@policy contains the scheduling policy.
 *	@lp contains the scheduling parameters.
 *	Return 0 if permission is granted.
 * @task_getscheduler:
 *	Check permission before obtaining scheduling information for process
 *	@p.
 *	@p contains the task_struct for process.
 *	Return 0 if permission is granted.
 * @task_kill:
 *	Check permission before sending signal @sig to @p.  @info can be NULL,
 *	the constant 1, or a pointer to a siginfo structure.  If @info is 1 or
 *	SI_FROMKERNEL(info) is true, then the signal should be viewed as coming
 *	from the kernel and should typically be permitted.
 *	SIGIO signals are handled separately by the send_sigiotask hook in
 *	file_security_ops.
 *	@p contains the task_struct for process.
 *	@info contains the signal information.
 *	@sig contains the signal value.
 *	Return 0 if permission is granted.
 * @task_wait:
 *	Check permission before allowing a process to reap a child process @p
 *	and collect its status information.
 *	@p contains the task_struct for process.
 *	Return 0 if permission is granted.
 * @task_prctl:
 *	Check permission before performing a process control operation on the
 *	current process.
 *	@option contains the operation.
 *	@arg2 contains a argument.
 *	@arg3 contains a argument.
 *	@arg4 contains a argument.
 *	@arg5 contains a argument.
 *	Return 0 if permission is granted.
 * @task_reparent_to_init:
 * 	Set the security attributes in @p->security for a kernel thread that
 * 	is being reparented to the init task.
 *	@p contains the task_struct for the kernel thread.
 * @task_to_inode:
 * 	Set the security attributes for an inode based on an associated task's
 * 	security attributes, e.g. for /proc/pid inodes.
 *	@p contains the task_struct for the task.
 *	@inode contains the inode structure for the inode.
 *
 * Security hooks for Netlink messaging.
 *
 * @netlink_send:
 *	Save security information for a netlink message so that permission
 *	checking can be performed when the message is processed.  The security
 *	information can be saved using the eff_cap field of the
 *      netlink_skb_parms structure.  Also may be used to provide fine
 *	grained control over message transmission.
 *	@sk associated sock of task sending the message.,
 *	@skb contains the sk_buff structure for the netlink message.
 *	Return 0 if the information was successfully saved and message
 *	is allowed to be transmitted.
 * @netlink_recv:
 *	Check permission before processing the received netlink message in
 *	@skb.
 *	@skb contains the sk_buff structure for the netlink message.
 *	Return 0 if permission is granted.
 *
 * Security hooks for Unix domain networking.
 *
 * @unix_stream_connect:
 *	Check permissions before establishing a Unix domain stream connection
 *	between @sock and @other.
 *	@sock contains the socket structure.
 *	@other contains the peer socket structure.
 *	Return 0 if permission is granted.
 * @unix_may_send:
 *	Check permissions before connecting or sending datagrams from @sock to
 *	@other.
 *	@sock contains the socket structure.
 *	@sock contains the peer socket structure.
 *	Return 0 if permission is granted.
 *
 * The @unix_stream_connect and @unix_may_send hooks were necessary because
 * Linux provides an alternative to the conventional file name space for Unix
 * domain sockets.  Whereas binding and connecting to sockets in the file name
 * space is mediated by the typical file permissions (and caught by the mknod
 * and permission hooks in inode_security_ops), binding and connecting to
 * sockets in the abstract name space is completely unmediated.  Sufficient
 * control of Unix domain sockets in the abstract name space isn't possible
 * using only the socket layer hooks, since we need to know the actual target
 * socket, which is not looked up until we are inside the af_unix code.
 *
 * Security hooks for socket operations.
 *
 * @socket_create:
 *	Check permissions prior to creating a new socket.
 *	@family contains the requested protocol family.
 *	@type contains the requested communications type.
 *	@protocol contains the requested protocol.
 *	@kern set to 1 if a kernel socket.
 *	Return 0 if permission is granted.
 * @socket_post_create:
 *	This hook allows a module to update or allocate a per-socket security
 *	structure. Note that the security field was not added directly to the
 *	socket structure, but rather, the socket security information is stored
 *	in the associated inode.  Typically, the inode alloc_security hook will
 *	allocate and and attach security information to
 *	sock->inode->i_security.  This hook may be used to update the
 *	sock->inode->i_security field with additional information that wasn't
 *	available when the ino