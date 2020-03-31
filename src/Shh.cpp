#include "plugin.hpp"


struct Shh : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		CV1_INPUT,
		CV2_INPUT,
		CV3_INPUT,
		CV4_INPUT,
		CV5_INPUT,
		CV6_INPUT,
		AUDIO1_INPUT,
		AUDIO2_INPUT,
		AUDIO3_INPUT,
		AUDIO4_INPUT,
		AUDIO5_INPUT,
		AUDIO6_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		AUDIO1_OUTPUT,
		AUDIO2_OUTPUT,
		AUDIO3_OUTPUT,
		AUDIO4_OUTPUT,
		AUDIO5_OUTPUT,
		AUDIO6_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		LED1,
		LED2,
		LED3,
		LED4,
		LED5,
		LED6,
		NUM_LIGHTS
	};

	Shh() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
		float voltThreshold = 2.5f;


		// goes through every input
		for(int i = 0; i < NUM_OUTPUTS){
			// if the CV voltage is above the threshold, allow audio to pass through (and turn the LED on)
			if(inputs[i].getVoltage() > voltThreshold){
				outputs[i].setVoltage(inputs[(2*i) - 1].getVoltage());
				lights[i].setBrightness(0.9f);
			}else{
				// otherwise just send no voltage, and turn the LED off
				outputs[i].setVoltage(0.0f);
				lights[i].setBrightness(0.0f);
			}
		}
	}
};


struct ShhWidget : ModuleWidget {
	ShhWidget(Shh* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Shh.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.058, 35.518)), module, Shh::AUDIO1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.058, 48.362)), module, Shh::AUDIO2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.058, 61.206)), module, Shh::AUDIO3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.058, 74.050)), module, Shh::AUDIO4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.058, 86.894)), module, Shh::AUDIO5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.058, 99.738)), module, Shh::AUDIO6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.241, 35.481)), module, Shh::CV1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.241, 48.325)), module, Shh::CV2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.241, 61.169)), module, Shh::CV3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.241, 74.013)), module, Shh::CV4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.241, 86.857)), module, Shh::CV5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.241, 99.702)), module, Shh::CV6_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(32.015, 35.481)), module, Shh::AUDIO1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(32.015, 48.325)), module, Shh::AUDIO2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(32.015, 61.169)), module, Shh::AUDIO3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(32.015, 74.013)), module, Shh::AUDIO4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(32.015, 86.857)), module, Shh::AUDIO5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(32.015, 99.702)), module, Shh::AUDIO6_OUTPUT));

		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(23.877, 32.128)), module, Shh::LED1));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(23.877, 44.951)), module, Shh::LED2));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(23.877, 57.775)), module, Shh::LED3));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(23.877, 70.599)), module, Shh::LED4));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(23.877, 83.423)), module, Shh::LED5));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(23.877, 96.246)), module, Shh::LED6));
	}
};


Model* modelShh = createModel<Shh, ShhWidget>("Shh");