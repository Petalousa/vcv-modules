
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
		PLAY_LIGHT,
		LOAD_LIGHT,
		NUM_LIGHTS
	};


	std::string fileUri = "";
	bool isFileLoaded = false;
	bool isPlaying = false;

	dsp::BooleanTrigger playTrigger;
	dsp::BooleanTrigger stopTrigger;
	dsp::BooleanTrigger loadTrigger;

	TextField *textField;

	MidiReader() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(PLAY_PARAM, 0.f, 1.f, 0.f, "");
		configParam(STOP_PARAM, 0.f, 1.f, 0.f, "");
		configParam(LOAD_PARAM, 0.f, 1.f, 0.f, "");
	}

	void setTextField(TextField *textField){
		this->textField = textField;
	}

	void setFile(std::string filepath){
		this->fileUri = filepath;
	}

	void process(const ProcessArgs& args) override {
		float voltThreshold = 2.5f;

		bool playTapped = params[PLAY_PARAM].getValue() > 0.0f || inputs[PLAY_INPUT].getVoltage() > voltThreshold;
		bool stopTapped = params[STOP_PARAM].getValue() > 0.0f || inputs[STOP_INPUT].getVoltage() > voltThreshold;
		bool loadTapped = params[LOAD_PARAM].getValue() > 0.0f;

		if (playTrigger.process(playTapped)){
			isPlaying = true;
		}
		if (stopTrigger.process(stopTapped)){
			isPlaying = false;
		}
		if (loadTrigger.process(loadTapped)){
			loadMidi();
		}

		if(isPlaying){
			lights[PLAY_LIGHT].setBrightness(1.0f);
		}else{
			lights[PLAY_LIGHT].setBrightness(0.0f);
		}

		if(isFileLoaded){
			lights[LOAD_LIGHT].setBrightness(1.0f);
		}else{
			lights[LOAD_LIGHT].setBrightness(0.0f);
		}
	}

	void loadMidi(){
		isFileLoaded = true;

		// TODO!
	}
	
	json_t* dataToJson() override {
		json_t *rootJ = json_object();

		json_object_set_new(rootJ, "file", json_string(fileUri.c_str()));
		
		return rootJ;
	}

	void dataFromJson(json_t* rootJ) override {
		json_t* textJ = json_object_get(rootJ, "file");
		if (textJ)
			this->fileUri = json_string_value(textJ);
	}

	
	void onReset() override {
		fileUri = "";
		isFileLoaded = false;
		isPlaying = false;
	}
	
	
};

struct LoadFileItem : MenuItem {
	MidiReader* module;
	
	void onAction(const event::Action& e) override {
		module->fileUri = "yellow";
	}
}

struct MidiReaderWidget : ModuleWidget {

	TextField* textField;
	
	MidiReaderWidget(MidiReader* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MidiReader.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<LEDBezel>(mm2px(Vec(21.375 + 6.0, 31.412 + 8.0)), module, MidiReader::PLAY_PARAM));
		addParam(createParamCentered<LEDBezel>(mm2px(Vec(21.375 + 6.0, 45.865 + 12.55)), module, MidiReader::STOP_PARAM));
		addParam(createParamCentered<LEDBezel>(mm2px(Vec(21.375 + 6.0, 60.318 + 16.3)), module, MidiReader::LOAD_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.712 + 9.0, 31.506 + 8.0)), module, MidiReader::PLAY_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.712 + 9.0, 46.005 + 12.55)), module, MidiReader::STOP_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(9.916 + 3.3, 84.686 + 23.7)), module, MidiReader::CV_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.883 + 6.5, 84.686 + 23.7)), module, MidiReader::GATE_OUTPUT));
	
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.877, 35.128)), module, MidiReader::PLAY_LIGHT));
		addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(20.877, 72.334)), module, MidiReader::LOAD_LIGHT));
	
		textField = createWidget<LedDisplayTextField>(mm2px(Vec(4.5, 15.0)));
		
		textField->box.size = mm2px(Vec(44.0, 14.0));
		textField->setModule(module);
		addChild(textField);	
	}

};


Model* modelMidiReader = createModel<MidiReader, MidiReaderWidget>("MidiReader");
