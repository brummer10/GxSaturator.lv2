// generated from file './/saturate.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace saturate {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	float 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
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
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
	float 	fSlow0 = (0.007000000000000006f * float(fslider0));
	float 	fSlow1 = (0.01f * float(fslider1));
	float 	fSlow2 = (1 - fSlow1);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993f * fRec0[1]) + fSlow0);
		float fTemp0 = (float)input0[i];
		float fTemp1 = max(-1.0f, min(1.0f, (fSlow1 * (fTemp0 * fRec0[0]))));
		float fTemp2 = ((8.276057040778557f * fTemp1) + ((0 - (2.634350774700782f * fTemp1)) * fabsf((6.5f * fTemp1))));
		float fTemp3 = ((7.002817496043395f * fTemp1) + ((0 - (2.229066040131431f * fTemp1)) * fabsf((5.5f * fTemp1))));
		float fTemp4 = ((5.729577951308232f * fTemp1) + ((0 - (1.82378130556208f * fTemp1)) * fabsf((4.5f * fTemp1))));
		float fTemp5 = ((4.45633840657307f * fTemp1) + ((0 - (1.4184965709927289f * fTemp1)) * fabsf((3.5f * fTemp1))));
		float fTemp6 = ((3.183098861837907f * fTemp1) + ((0 - (1.0132118364233778f * fTemp1)) * fabsf((2.5f * fTemp1))));
		float fTemp7 = ((1.909859317102744f * fTemp1) + ((0 - (0.6079271018540267f * fTemp1)) * fabsf((1.5f * fTemp1))));
		float fTemp8 = ((0.6366197723675814f * fTemp1) + ((0 - (0.20264236728467555f * fTemp1)) * fabsf((0.5f * fTemp1))));
		output0[i] = (FAUSTFLOAT)((fSlow2 * fTemp0) + (0.6666666666666666f * ((((((((fTemp8 + (0.225f * ((fTemp8 * fabsf(fTemp8)) - fTemp8))) + (0.3f * (fTemp7 + (0.225f * ((fTemp7 * fabsf(fTemp7)) - fTemp7))))) + (0.15f * (fTemp6 + (0.225f * ((fTemp6 * fabsf(fTemp6)) - fTemp6))))) + (0.075f * (fTemp5 + (0.225f * ((fTemp5 * fabsf(fTemp5)) - fTemp5))))) + (0.0375f * (fTemp4 + (0.225f * ((fTemp4 * fabsf(fTemp4)) - fTemp4))))) + (0.01875f * (fTemp3 + (0.225f * ((fTemp3 * fabsf(fTemp3)) - fTemp3))))) + (0.009375f * (fTemp2 + (0.225f * ((fTemp2 * fabsf(fTemp2)) - fTemp2))))) / fRec0[0])));
		// post processing
		fRec0[1] = fRec0[0];
	}
#undef fslider0
#undef fslider1
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case INTENSITY: 
		fslider0_ = (float*)data; // , 6.0f, 1.0f, 1e+01f, 0.01f 
		break;
	case SATURATE: 
		fslider1_ = (float*)data; // , 6e+01f, 0.0f, 1e+02f, 1.0f 
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
   INTENSITY, 
   SATURATE, 
} PortIndex;
*/

} // end namespace saturate
