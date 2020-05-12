
mod_sign_cmd = scripts/sign-file $(CONFIG_MODULE_SIG_HASH) \
$(MODULE_SIG_KEY_SRCPREFIX)

else

mod_sign_cmd = true
endif

export mod_sign_cmd

ifeq ( $(KBUILD_EXTMOD),)
core-y    += kernel / certs / mm / fs/ ipc/ security/ crypto/ block/ hellosys/

vmlinux-dirs := $(patsubst %/, %, $(filter %/, $(init-y) $(init-m) \
$(core-y) $(core-m) $(drivers-y) $(drivers-m) \
$(net-y) $(net-m) $(libs-y) $(libs-m) $(virt-y)))

vmlinux-alldirs := $(sort $(vmlinux-dirs) $(patsubst %/, %, $(filter %/, \
$(init-) $(core-) $(drivers-) $(net-) $(libs-) $(virst-))))
