/*
  ==============================================================================


    Created: 24 Feb 2017 10:19:53am
    Author:  Michelangelo Nottoli

  ==============================================================================
*/


PerformanceValue::PerformanceValue():value_(0.0),peak_(DBL_MAX)
{
};
PerformanceValue::~PerformanceValue()
{
};

void PerformanceValue::init(double sampleRate, double smoothTime){
    value_ = 0.0;
    peak_ = DBL_MAX;
    valueSmoother_.reset(sampleRate, smoothTime);
}

void PerformanceValue::start(){
    measureStart_ = Time::getHighResolutionTicks();
}


void PerformanceValue::end(double referenceMilliseconds){
    int64 measureEnd = Time::getHighResolutionTicks();
    
    double newValue = referenceMilliseconds/(Time::highResolutionTicksToSeconds(measureEnd-measureStart_)*1000.0);
    peak_=jmin(peak_,newValue);
    
    valueSmoother_.setValue(newValue);
    
    value_ = valueSmoother_.getNextValue();
}

double PerformanceValue::get(){
    return value_;
}

double PerformanceValue::peak(){
    return peak_;
}

