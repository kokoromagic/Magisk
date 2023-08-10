#pragma once

#define JAVA_PACKAGE_NAME "com.topjohnwu.magisk"
// magiskinit will hex patch this constant,
// appending \0 to prevent the compiler from reusing the string for "1"
#define RANDOM_SOCKET_NAME  "d30138f2310a9fb9c54a3e0c21f58591\0"

#define ZYGISKLDR       "libzygisk.so"
#define NBPROP          "ro.dalvik.vm.native.bridge"
#define SECURE_DIR      "/data/adb"
#define MODULEROOT      SECURE_DIR "/modules"
#define MODULEUPGRADE   SECURE_DIR "/modules_update"
#define DATABIN         SECURE_DIR "/magisk"
#define MAGISKDB        SECURE_DIR "/magisk.db"

// tmpfs paths
#define INTLROOT      ".magisk"
#define MIRRDIR       INTLROOT "/mirror"
#define PREINITMIRR   INTLROOT "/preinit"
#define BLOCKDIR      INTLROOT "/block"
#define PREINITDEV    BLOCKDIR "/preinit"
#define WORKERDIR     INTLROOT "/worker"
#define MODULEMNT     INTLROOT "/modules"
#define BBPATH        INTLROOT "/busybox"
#define ROOTOVL       INTLROOT "/rootdir"
#define SHELLPTS      INTLROOT "/pts"
#define ROOTMNT       ROOTOVL  "/.mount_list"
#define SELINUXMOCK   INTLROOT "/selinux"
#define MAIN_CONFIG   INTLROOT "/config"
#define MAIN_SOCKET   INTLROOT "/socket"
#define LOG_PIPE      INTLROOT "/log"
#define EARLYMNT      INTLROOT "/early-mount.d"

constexpr const char *applet_names[] = { "su", "resetprop", nullptr };

#define POST_FS_DATA_WAIT_TIME       40
#define POST_FS_DATA_SCRIPT_MAX_TIME 35

// Unconstrained domain the daemon and root processes run in
#define SEPOL_PROC_DOMAIN   "magisk"
#define MAGISK_PROC_CON     "u:r:" SEPOL_PROC_DOMAIN ":s0"
// Unconstrained file type that anyone can access
#define SEPOL_FILE_TYPE     "magisk_file"
#define MAGISK_FILE_CON     "u:object_r:" SEPOL_FILE_TYPE ":s0"
// Log pipe that only root and zygote can open
#define SEPOL_LOG_TYPE      "magisk_log_file"
#define MAGISK_LOG_CON      "u:object_r:" SEPOL_LOG_TYPE ":s0"

extern int SDK_INT;
#define APP_DATA_DIR (SDK_INT >= 24 ? "/data/user_de" : "/data/user")

// Multi-call entrypoints
int magisk_main(int argc, char *argv[]);
int su_client_main(int argc, char *argv[]);
int resetprop_main(int argc, char *argv[]);
int zygisk_main(int argc, char *argv[]);
