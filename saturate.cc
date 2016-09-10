// generated from file './/saturate.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace saturate {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	void connect(uint32_t port,void* data);
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "sat";
	name = N_("Saturate");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = 0;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
	double 	fSlow0 = double(fslider0);
	double 	fSlow1 = (0.065 * fSlow0);
	double 	fSlow2 = (0.055 * fSlow0);
	double 	fSlow3 = (0.045 * fSlow0);
	double 	fSlow4 = (0.035 * fSlow0);
	double 	fSlow5 = (0.025 * fSlow0);
	double 	fSlow6 = (0.015 * fSlow0);
	double 	fSlow7 = (0.005 * fSlow0);
	double 	fSlow8 = (1 - (0.01 * fSlow0));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		output0[i] = (FAUSTFLOAT)((fSlow8 * fTemp0) + (0.6666666666666666 * ((((((sin((fSlow7 * fTemp0)) + (0.3 * sin((fSlow6 * fTemp0)))) + (0.15 * sin((fSlow5 * fTemp0)))) + (0.075 * sin((fSlow4 * fTemp0)))) + (0.0375 * sin((fSlow3 * fTemp0)))) + (0.01875 * sin((fSlow2 * fTemp0)))) + (0.009375 * sin((fSlow1 * fTemp0))))));
	}
#undef fslider0
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case SATURATE: 
		fslider0_ = (float*)data; // , 1e+02, 0.0, 1e+02, 1.0 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   SATURATE, 
} PortIndex;
*/

} // end namespace saturate
