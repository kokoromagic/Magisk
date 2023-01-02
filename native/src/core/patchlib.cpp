#include <sys/mman.h>
#include <sys/mount.h>

#include <magisk.hpp>
#include <daemon.hpp>
#include <base.hpp>

using namespace std;

#define VLOGD(tag, from, to) LOGD("%-8s: %s <- %s\n", tag, to, from)
#define XLOGD(tag, log)      LOGD("%-8s: %s\n", tag, log)

static int bind_mount(const char *reason, const char *from, const char *to) {
    int ret = xmount(from, to, nullptr, MS_BIND | MS_REC, nullptr);
    if (ret == 0)
        VLOGD(reason, from, to);
    return ret;
}

static void hex2byte(const char *hex, uint8_t *buf) {
    char high, low;
    for (int i = 0, length = strlen(hex); i < length; i += 2) {
        high = toupper(hex[i]) - '0';
        low = toupper(hex[i + 1]) - '0';
        buf[i / 2] = ((high > 9 ? high - 7 : high) << 4) + (low > 9 ? low - 7 : low);
    }
}

static int hexpatch(const char *file, const char *from, const char *to) {
    int patched = 1;

    auto m = mmap_data(file, true);

    vector<uint8_t> pattern(strlen(from) / 2);
    vector<uint8_t> patch(strlen(to) / 2);

    hex2byte(from, pattern.data());
    hex2byte(to, patch.data());

    uint8_t * const end = m.buf + m.sz;
    for (uint8_t *curr = m.buf; curr < end; curr += pattern.size()) {
        curr = static_cast<uint8_t*>(memmem(curr, end - curr, pattern.data(), pattern.size()));
        if (curr == nullptr)
            return patched;
        LOGD("hexpatch: @ %08X [%s] -> [%s]\n", (unsigned)(curr - m.buf), from, to);
        memset(curr, 0, pattern.size());
        memcpy(curr, patch.data(), patch.size());
        patched = 0;
    }

    return patched;
}

void zygisk_patch_libanroid_runtime() {
    const char *hex1 = "726f2e64616c76696b2e766d2e6e61746976652e62726964676500";
    const char *hex2 = "726f2e7a79676f7465000000000000000000000000000000000000";
    string patchlib = MAGISKTMP + "/" ZYGISKBIN "/libandroid_runtime.so";
    if (access(LIBRUNTIME32, F_OK) == 0) {
        XLOGD("zygisk", "patch " LIBRUNTIME32);
        string patchlib32 = patchlib + ".32";
        cp_afc(LIBRUNTIME32, patchlib32.data());
        hexpatch(patchlib32.data(), hex1, hex2);
        bind_mount("zygisk", patchlib32.data(), LIBRUNTIME32);
    }
    if (access(LIBRUNTIME64, F_OK) == 0) {
        XLOGD("zygisk", "patch " LIBRUNTIME64);
        string patchlib64 = patchlib + ".64";
        cp_afc(LIBRUNTIME64, patchlib64.data());
        hexpatch(patchlib64.data(), hex1, hex2);
        bind_mount("zygisk", patchlib64.data(), LIBRUNTIME64);
    }
}
