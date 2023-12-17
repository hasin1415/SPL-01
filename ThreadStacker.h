//
// Created by ASUS on 12/16/2023.
//

#ifndef SPL_01_THREADSTACKER_H
#define SPL_01_THREADSTACKER_H


#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include "Image.h"
#include "Stacker.h"

class ThreadStacker {
public:
    int add(int a, int b) {
        return a + b;
    }
    Image stackImage(const Image& One, const Image& Two){
        int width = One.getMWidth();
        int height = One.getMHeight();
        Image result(width, height);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                Color colorOne = One.GetColor(i, j);
                Color colorTwo = Two.GetColor(i, j);
                Color averageColor((colorOne.red + colorTwo.red) / 2.0,
                                   (colorOne.green + colorTwo.green) / 2.0,
                                   (colorOne.blue + colorTwo.blue) / 2.0);
                result.SetColor(averageColor, i, j);
            }
        }
        return result;
    }

    /* int sumVectorWithThreads(std::vector<int>& vec) {
         const int numThreads = 5;
         std::vector<std::thread> threads;

         for (int i = 0; i < numThreads; ++i) {
             threads.emplace_back(&Adder::threadFunction, this, std::ref(vec));
         }

         for (auto& thread : threads) {
             thread.join();
         }

         int sum = 0;
         for (int num : vec) {
             sum += num;
         }

         return sum;
     }
     */
    Image sumImagesWithThreads(std::vector<Image>& vec) {
        const int numThreads = 5;
        std::vector<std::thread> threads;

        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back(&ThreadStacker::threadFunction, this, std::ref(vec));
        }

        for (auto& thread : threads) {
            thread.join();
        }

        Image sum = vec[0];
        for (int i = 1; i < vec.size(); ++i) {
            sum = stackImage(sum, vec[i]);
        }

        return sum;
    }

private:
    std::mutex vectorMutex;
    void threadFunction(std::vector<Image>& vec) {
        while (true) {
            std::lock_guard<std::mutex> lock(vectorMutex);
            if (vec.size() < 2) {
                break;
            }
            Image a = vec.back();
            vec.pop_back();
            Image b = vec.back();
            vec.pop_back();
            Image result = stackImage(a, b);
            vec.push_back(result);
        }
    }
};



#endif //SPL_01_THREADSTACKER_H
