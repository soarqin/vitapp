#include "app.hh"

#include <vita2d.h>

#include <psp2/apputil.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/message_dialog.h>
#include <psp2/sysmodule.h>

#include <algorithm>

enum {
    SCE_SYSMODULE_PAF = 0x80000008,
    SCE_SYSMODULE_PROMOTER_UTIL = 0x80000024,
};

int sceSysmoduleLoadModuleInternal(SceUInt32 id);
int sceSysmoduleUnloadModuleInternal(SceUInt32 id);
int sceSysmoduleIsLoadedInternal(SceUInt32 id);
int sceSysmoduleLoadModuleInternalWithArg(SceUInt32 id, SceSize size, ScePVoid argp, ScePVoid ptr);

namespace vitapp {

app *app::app_ = nullptr;

// aux function to check value in container or not
template <typename C, typename T>
inline bool is_in(const C &c, const T &val) {
    return c.find(val) != c.end();
}

app::app(const std::initializer_list<module> &inits) {
    inited_modules_ = inits;

    SceAppUtilInitParam init_param;
    SceAppUtilBootParam boot_param;

    SceCommonDialogConfigParam config;

    memset(&init_param, 0, sizeof(SceAppUtilInitParam));
    memset(&boot_param, 0, sizeof(SceAppUtilBootParam));
    sceAppUtilInit(&init_param, &boot_param);

    sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, &language_);
    sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, &enter_button_);

    // Mount
    sceAppUtilMusicMount();
    sceAppUtilPhotoMount();

    sceCommonDialogConfigParamInit(&config);
    config.language = language_;
    config.enterButtonAssign = enter_button_;
    sceCommonDialogSetConfigParam(&config);
    if (is_in(inited_modules_, module::net)) {
        load(module::net);
    }
    if (is_in(inited_modules_, module::pgf)) {
        load(module::pgf);
    }
    if (is_in(inited_modules_, module::promoter)) {
        load(module::vita2d);
    }
    if (is_in(inited_modules_, module::vita2d)) {
        load(module::vita2d);
    }
}

app::~app() {
    free_font();
    if (is_in(inited_modules_, module::vita2d)) {
        vita2d_fini();
    }
    if (is_in(inited_modules_, module::promoter)) {
        if (sceSysmoduleIsLoadedInternal(SCE_SYSMODULE_PROMOTER_UTIL) == SCE_SYSMODULE_LOADED)
            sceSysmoduleUnloadModuleInternal(SCE_SYSMODULE_PROMOTER_UTIL);
        if (sceSysmoduleIsLoadedInternal(SCE_SYSMODULE_PAF) == SCE_SYSMODULE_LOADED)
            sceSysmoduleUnloadModuleInternal(SCE_SYSMODULE_PAF);
    }
    if (is_in(inited_modules_, module::pgf)) {
        if (sceSysmoduleIsLoaded(SCE_SYSMODULE_PGF) == SCE_SYSMODULE_LOADED)
            sceSysmoduleUnloadModule(SCE_SYSMODULE_PGF);
    }
    if (is_in(inited_modules_, module::net)) {
        if (sceSysmoduleIsLoaded(SCE_SYSMODULE_NET) == SCE_SYSMODULE_LOADED)
            sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);
    }

    // Unmount
    sceAppUtilPhotoUmount();
    sceAppUtilMusicUmount();

    // Shutdown AppUtil
    sceAppUtilShutdown();

    sceKernelExitProcess(0);
}

void app::init_font(const char *name) {
    if (!is_in(inited_modules_, module::vita2d)) {
        vita2d_init();
        inited_modules_.insert(module::vita2d);
    }
    free_font();
    if (name == nullptr)
        font_ = vita2d_load_default_pgf();
    else
        font_ = vita2d_load_custom_pgf(name);
}

void app::free_font() {
    if (font_ != nullptr) {
        vita2d_free_pgf((vita2d_pgf *)font_);
        font_ = nullptr;
    }
}

void app::run() {

}

void app::load(app::module m, bool check) {
    if (check) {
        if (is_in(inited_modules_, m)) return;
        inited_modules_.insert(m);
    }
    switch (m){
    case module::net:
        if (sceSysmoduleIsLoaded(SCE_SYSMODULE_NET) != SCE_SYSMODULE_LOADED)
            sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
        break;
    case module::pgf:
        if (sceSysmoduleIsLoaded(SCE_SYSMODULE_PGF) != SCE_SYSMODULE_LOADED)
            sceSysmoduleLoadModule(SCE_SYSMODULE_PGF);
        break;
    case module::promoter: {
        if (sceSysmoduleIsLoadedInternal(SCE_SYSMODULE_PAF) != SCE_SYSMODULE_LOADED) {
            uint32_t ptr[0x100] = {0};
            ptr[0] = 0;
            ptr[1] = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&ptr[0]));
            uint32_t scepaf_argp[] = {0x400000, 0xEA60, 0x40000, 0, 0};
            sceSysmoduleLoadModuleInternalWithArg(SCE_SYSMODULE_PAF, sizeof(scepaf_argp), scepaf_argp, ptr);
        }
        if (sceSysmoduleIsLoaded(SCE_SYSMODULE_PGF) != SCE_SYSMODULE_LOADED)
            sceSysmoduleLoadModuleInternal(SCE_SYSMODULE_PROMOTER_UTIL);
        break;
    }
    case module::vita2d:
        vita2d_init();
        break;
    }
}

}
