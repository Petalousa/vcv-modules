#include "plugin.hpp"


struct MidiReader : Module {
	enum ParamIds {
		PLAY_PARAM,
		STOP_PARAM,
		LOAD_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		PLAY_INPUT,
		STOP_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		CV_OUTPUT,
		GATE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	dsp::BooleanTrigger playTrigger;
	dsp::BooleanTrigger stopTrigger;
	dsp::BooleanTrigger loadTrigger;
	

	MidiReader() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(PLAY_PARAM, 0.f, 1.f, 0.f, "");
		configParam(STOP_PARAM, 0.f, 1.f, 0.f, "");
		configParam(LOAD_PARAM, 0.f, 1.f, 0.f, "");
	}



	void process(const ProcessArgs& args) override {
		float voltThreshold = 2.5f;

		bool playTapped = params[PLAY_PARAM].getValue() > 0.0f || inputs[PLAY_INPUT].getVoltage() > voltThreshold;
		bool stopTapped = params[STOP_PARAM].getValue() > 0.0f || inputs[STOP_INPUT].getVoltage() > voltThreshold;
		bool loadTapped = params[LOAD_PARAM].getValue() > 0.0f;

		if (playTrigger.process(playTapped)){
			// play button hit
		}
		if (stopTrigger.process(stopTapped)){
			// stop button hit
		}
		if (loadTrigger.process(loadTapped)){
			// load button hit
		}

	}

	
};


struct MidiReaderWidget : ModuleWidget {
	TextField* textField;

	MidiReaderWidget(MidiReader* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MidiReader.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<LEDBezel>(mm2px(Vec(21.375, 31.412)), module, MidiReader::PLAY_PARAM));
		addParam(createParamCentered<LEDBezel>(mm2px(Vec(21.375, 45.865)), module, MidiReader::STOP_PARAM));
		addParam(createParamCentered<LEDBezel>(mm2px(Vec(21.375, 60.318)), module, MidiReader::LOAD_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.712, 31.506)), module, MidiReader::PLAY_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.712, 46.005)), module, MidiReader::STOP_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(9.916 + 5.0, 84.686 + 20.0)), module, MidiReader::CV_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.883 + 5.0, 84.686 + 20.0)), module, MidiReader::GATE_OUTPUT));
		// + 

		textField = createWidget<LedDisplayTextField>(mm2px(Vec(4.5, 16.0)));
		textField->box.size = mm2px(Vec(36.0, 10.657));
		textField->multiline = true;
		addChild(textField);
	}
};


Model* modelMidiReader = createModel<MidiReader, MidiReaderWidget>("MidiReader");