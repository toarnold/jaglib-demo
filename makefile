DEMOS = 01Hello 02Input 03Counter 04Bitmap 05Square \
		06Hidden 07Flicker 08Stick 09Sine 10Fractal 11Debug \
		12GpuTimerCpu 13DspTimerDsp

define cleandemo
	make -C $(1) clean
endef

define demo
	make -C $(1) run
	@read -p "Press any key to continue..." -n 1 -s
endef

all:
	$(foreach var,$(DEMOS), $(call demo,$(var));)
	
clean:
	$(foreach var,$(DEMOS), $(call cleandemo,$(var));)
