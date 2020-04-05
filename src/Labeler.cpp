#include "plugin.hpp"


struct Labeler : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		RECT56657_INPUT,
		RECT56659_INPUT,
		RECT56661_INPUT,
		RECT56663_INPUT,
		RECT56665_INPUT,
		RECT56667_INPUT,
		RECT56669_INPUT,
		RECT56671_INPUT,
		RECT56673_INPUT,
		RECT56675_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		RECT56677_OUTPUT,
		RECT56679_OUTPUT,
		RECT56681_OUTPUT,
		RECT56683_OUTPUT,
		RECT56685_OUTPUT,
		RECT56687_OUTPUT,
		RECT56689_OUTPUT,
		RECT56691_OUTPUT,
		RECT56693_OUTPUT,
		RECT56695_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	Labeler() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
		// output the same input voltage
		for(int i = 0; i < NUM_OUTPUTS; i++){
			outputs[i].setVoltage(inputs[i].getNormalVoltage(0.0f));
		}
	}
};


struct LabelerWidget : ModuleWidget {
	TextField* textFields[10];


	LabelerWidget(Labeler* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Labeler.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		float y_base = 12.863f + 2.864f;
		float y_space = 10.0f;
		for(int i =0; i<10; i++){
			addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, y_base + (float)i * y_space)), module, i));
		}	
		
		for(int i =0; i<10; i++){
			addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, y_base + (float)i * y_space)), module, i));
		}

/*
		addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, -12.863 + (12.863 + 2.864))), module, Labeler::RECT56657_INPUT));
		addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, -2.864)), module, Labeler::RECT56659_INPUT));
		addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, 7.136)), module, Labeler::RECT56661_INPUT));
		addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, 17.136)), module, Labeler::RECT56663_INPUT));
		addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, 27.137)), module, Labeler::RECT56665_INPUT));
		addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, 37.136)), module, Labeler::RECT56667_INPUT));
		addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, 47.136)), module, Labeler::RECT56669_INPUT));
		addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, 57.137)), module, Labeler::RECT56671_INPUT));
		addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, 67.136)), module, Labeler::RECT56673_INPUT));
		addInput(createInput<PJ301MPort>(mm2px(Vec(4.83, 77.136)), module, Labeler::RECT56675_INPUT));

		addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, -12.863)), module, Labeler::RECT56677_OUTPUT));
		addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, -2.864)), module, Labeler::RECT56679_OUTPUT));
		addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, 7.136)), module, Labeler::RECT56681_OUTPUT));
		addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, 17.136)), module, Labeler::RECT56683_OUTPUT));
		addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, 27.136)), module, Labeler::RECT56685_OUTPUT));
		addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, 37.136)), module, Labeler::RECT56687_OUTPUT));
		addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, 47.136)), module, Labeler::RECT56689_OUTPUT));
		addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, 57.137)), module, Labeler::RECT56691_OUTPUT));
		addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, 67.136)), module, Labeler::RECT56693_OUTPUT));
		addOutput(createOutput<PJ301MPort>(mm2px(Vec(38.355, 77.136)), module, Labeler::RECT56695_OUTPUT));
	*/

		for(int i =0; i<10; i++){
			textFields[i] = createWidget<LedDisplayTextField>(mm2px(Vec(14.356, y_base + (float)i * y_space)));
			textFields[i]->box.size = mm2px(Vec(22.412, 8.212));
			addChild(textFields[i]);
		}

		/*
		// mm2px(Vec(22.412, 8.212))
		addChild(createWidget<Widget>(mm2px(Vec(14.356, -12.863))));
		// mm2px(Vec(22.412, 8.212))
		addChild(createWidget<Widget>(mm2px(Vec(14.356, -1.592))));
		// mm2px(Vec(22.412, 8.212))
		addChild(createWidget<Widget>(mm2px(Vec(14.356, 7.668))));
		// mm2px(Vec(22.412, 8.212))
		addChild(createWidget<Widget>(mm2px(Vec(14.356, 18.384))));
		// mm2px(Vec(22.412, 8.212))
		addChild(createWidget<Widget>(mm2px(Vec(14.356, 27.38))));
		// mm2px(Vec(22.412, 8.212))
		addChild(createWidget<Widget>(mm2px(Vec(14.356, 35.978))));
		// mm2px(Vec(22.412, 8.212))
		addChild(createWidget<Widget>(mm2px(Vec(14.356, 46.033))));
		// mm2px(Vec(22.412, 8.212))
		addChild(createWidget<Widget>(mm2px(Vec(14.356, 54.764))));
		// mm2px(Vec(22.412, 8.212))
		addChild(createWidget<Widget>(mm2px(Vec(14.356, 66.406))));
		// mm2px(Vec(22.412, 8.212))
		addChild(createWidget<Widget>(mm2px(Vec(14.356, 77.136))));
		*/

	}

	json_t* toJson() override {
			json_t* rootJ = ModuleWidget::toJson();

			std::string str;
			
			// text
			for(int i = 0; i < 10; i++){
				str = "text";
				str.append(std::to_string(i));
				json_object_set_new(rootJ, (str).c_str(), json_string(textFields[i]->text.c_str()));
			}

			return rootJ;
		}

		void fromJson(json_t* rootJ) override {
			ModuleWidget::fromJson(rootJ);

			std::string str;
			
			// text
			for(int i = 0; i < 10; i++){
				str = "text";
				str.append(std::to_string(i));
				
				json_t* textJ = json_object_get(rootJ, str.c_str());
				if (textJ)
					textFields[i]->text = json_string_value(textJ);
			}
			
		}
};


Model* modelLabeler = createModel<Labeler, LabelerWidget>("Labeler");