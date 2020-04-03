#include "plugin.hpp"


struct MidiReader : Module {
	enum ParamIds {
		CIRCLE7554_PARAM,
		CIRCLE7554_2_PARAM,
		CIRCLE7554_9_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CIRCLE7554_2_7_INPUT,
		CIRCLE7554_2_0_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		CIRCLE7490_OUTPUT,
		CIRCLE7490_0_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	MidiReader() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(CIRCLE7554_PARAM, 0.f, 1.f, 0.f, "");
		configParam(CIRCLE7554_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(CIRCLE7554_9_PARAM, 0.f, 1.f, 0.f, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct MidiReaderWidget : ModuleWidget {
	MidiReaderWidget(MidiReader* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MidiReader.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(21.375, 31.412)), module, MidiReader::CIRCLE7554_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(21.375, 45.865)), module, MidiReader::CIRCLE7554_2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(21.375, 60.318)), module, MidiReader::CIRCLE7554_9_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.712, 31.506)), module, MidiReader::CIRCLE7554_2_7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.712, 46.005)), module, MidiReader::CIRCLE7554_2_0_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(9.916, 84.686)), module, MidiReader::CIRCLE7490_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.883, 84.686)), module, MidiReader::CIRCLE7490_0_OUTPUT));

		// mm2px(Vec(30.824, 9.657))
		addChild(createWidget<Widget>(mm2px(Vec(4.498, 12.039))));
	}
};


Model* modelMidiReader = createModel<MidiReader, MidiReaderWidget>("MidiReader");