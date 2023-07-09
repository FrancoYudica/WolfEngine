#pragma once
#ifndef WOLF_RANDOM_H
#define WOLF_RANDOM_H
#include <stdint.h>
#include <random>

namespace Wolf
{
    namespace Numerical
    {
        
        namespace Random
        {
            class RandomFloat
            {
            
                public:
                    RandomFloat(uint32_t seed=0);
                    float unit();
                    float range(float min, float max);
                    float signed_unit();
    
                private:
                    std::uniform_real_distribution<float> _distribution;
                    std::mt19937 _generator;
                    uint32_t _seed;
            };
    
            class RandomDouble
            {
            
                public:
                    RandomDouble(uint32_t seed=0);
                    double unit();
                    double range(double min, double max);
                    double signed_unit();
    
                private:
                    std::uniform_real_distribution<double> _distribution;
                    std::mt19937 _generator;
                    uint32_t _seed;
            };


            class RandomInt
            {
            
                public:
                    RandomInt(uint32_t seed=0);
                    int32_t unit();
                    int32_t range(int32_t min, int32_t max);
                    int32_t signed_unit();
    
                private:
                    std::uniform_int_distribution<int32_t> _distribution;
                    std::mt19937 _generator;
                    uint32_t _seed;
            };
    
            // Generic use static instances
            static thread_local RandomFloat RandomFloatGenerator;
            static thread_local RandomDouble RandomDoubleGenerator;
            static thread_local RandomInt RandomIntGenerator;
    
            // Access to float methods
            static float unit_f() { return RandomFloatGenerator.unit(); }
            static float signed_unit_f() { return RandomFloatGenerator.signed_unit(); }
            static float range_f(float min, float max) { return RandomFloatGenerator.range(min, max); }
    
            // Access to double methods
            static double unit_d() { return RandomDoubleGenerator.unit(); }
            static double signed_unit_d() { return RandomDoubleGenerator.signed_unit(); }
            static double range_d(double min, double max) { return RandomDoubleGenerator.range(min, max); }
            
            // Access to double methods

            /// @brief Returns an integer in the range [0, max(int32_t)]
            static int32_t unit_i() { return RandomIntGenerator.unit(); }
            static int32_t signed_unit_i() { return RandomIntGenerator.signed_unit(); }
            static int32_t range_i(int32_t min, int32_t max) { return RandomIntGenerator.range(min, max); }
            

        }
    }
}


#endif