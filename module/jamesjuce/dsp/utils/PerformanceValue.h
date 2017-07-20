/*
  ==============================================================================

    juls_PuginProcessorState.h
    Created: 24 Feb 2017 10:19:53am
    Author:  Michelangelo Nottoli

  ==============================================================================
*/

#pragma once


    /**
     
     smoothed preformance value:
      - initialize once calling init(sampleRate,smoothTime)
      - for every measure call start (), then end(referenceMilliseconds)
        -referenceMilliseconds is the input time (audiobuffer frames or timer )
    
     
         if it takes 1ms to process 10ms of audio frames (or a timer set at 10ms)
         the performance value will be 10.
         Just like CD ripping "at 10X"
    */
    
    class PerformanceValue{
    
    public:
        
        PerformanceValue();
        virtual ~PerformanceValue();
        
        void init(double sampleRate, double smoothTime);
        
        void start();
        

        void end(double referenceMilliseconds);
        
        double get();
        double peak();
        
        
    private:
        double value_;
        LinearSmoothedValue<double> valueSmoother_; // uses juce smoother (other smoothers moved in fefanto_DSP
        double peak_;
        int64 measureStart_;
        
    };
    
    
