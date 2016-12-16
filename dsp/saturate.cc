// generated from file './/saturate.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace saturate {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
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
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.01 * double(fslider1));
	double 	fSlow2 = (1 - fSlow1);
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		double fTemp0 = (double)input0[i];
		double fTemp1 = max(-1.0, min(1.0, (fSlow1 * (fTemp0 * fRec0[0]))));
		double fTemp2 = ((8.276057040778557 * fTemp1) + ((0 - (2.634350774700782 * fTemp1)) * fabs((6.5 * fTemp1))));
		double fTemp3 = ((7.002817496043395 * fTemp1) + ((0 - (2.229066040131431 * fTemp1)) * fabs((5.5 * fTemp1))));
		double fTemp4 = ((5.729577951308232 * fTemp1) + ((0 - (1.82378130556208 * fTemp1)) * fabs((4.5 * fTemp1))));
		double fTemp5 = ((4.45633840657307 * fTemp1) + ((0 - (1.4184965709927289 * fTemp1)) * fabs((3.5 * fTemp1))));
		double fTemp6 = ((3.183098861837907 * fTemp1) + ((0 - (1.0132118364233778 * fTemp1)) * fabs((2.5 * fTemp1))));
		double fTemp7 = ((1.909859317102744 * fTemp1) + ((0 - (0.6079271018540267 * fTemp1)) * fabs((1.5 * fTemp1))));
		double fTemp8 = ((0.6366197723675814 * fTemp1) + ((0 - (0.20264236728467555 * fTemp1)) * fabs((0.5 * fTemp1))));
		output0[i] = (FAUSTFLOAT)((fSlow2 * fTemp0) + (0.6666666666666666 * ((((((((fTemp8 + (0.225 * ((fTemp8 * fabs(fTemp8)) - fTemp8))) + (0.3 * (fTemp7 + (0.225 * ((fTemp7 * fabs(fTemp7)) - fTemp7))))) + (0.15 * (fTemp6 + (0.225 * ((fTemp6 * fabs(fTemp6)) - fTemp6))))) + (0.075 * (fTemp5 + (0.225 * ((fTemp5 * fabs(fTemp5)) - fTemp5))))) + (0.0375 * (fTemp4 + (0.225 * ((fTemp4 * fabs(fTemp4)) - fTemp4))))) + (0.01875 * (fTemp3 + (0.225 * ((fTemp3 * fabs(fTemp3)) - fTemp3))))) + (0.009375 * (fTemp2 + (0.225 * ((fTemp2 * fabs(fTemp2)) - fTemp2))))) / fRec0[0])));
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
		fslider0_ = (float*)data; // , 6.0, 1.0, 1e+01, 0.01 
		break;
	case SATURATE: 
		fslider1_ = (float*)data; // , 6e+01, 0.0, 1e+02, 1.0 
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
