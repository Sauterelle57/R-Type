/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Random
*/

#ifndef RANDOM_HPP_
#define RANDOM_HPP_
#include <cstdlib>

namespace tls {
    class Random {
        public:
            Random(int seed = 0) {
                setSeed(seed);
            }

            void setSeed(int seed) {
                srand(seed);
            }

            // get random number between min and max (include)
            int getRandomNumber(int min, int max) {
                return min + rand() % (max - min + 1);
            }

            double getRandomDouble(double min, double max) {
                return min + (max - min) * (rand() / (RAND_MAX + 1.0));
            }
    };
} // tls

#endif /* !RANDOM_HPP_ */
