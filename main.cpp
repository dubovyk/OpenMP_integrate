#include <iostream>
#include <cmath>
#include <omp.h>
#include <fstream>
#include <fcntl.h>
#include <zconf.h>
#include <sstream>
#include <map>

#include "inc/t_measure.h"

struct config{
    int x_begin;
    int x_end;
    int y_begin;
    int y_end;
    double step;
};

double f(double x, double y)
{
    double result = 0.002;
    for(int i = -2; i <= 2; i++)
    {
        for(int j = -2; j<=2; j++)
        {
            double temp_res = 1 / (5*(i+2) + j + 3 + std::pow(x - 16*j, 6) + std::pow(y - 16*i, 6));
            result += std::abs(temp_res);
        }
    }
    return 1.0 / result;
}


double integrate(config conf){
    unsigned long sectors = (conf.x_end - conf.x_begin) / conf.step;
    double xInterval = std::abs((conf.x_begin - conf.x_end)) / (double)sectors;
    double result = 0;

    #pragma omp parallel for
    for(int i = 0; i < sectors; i++){
        double x_from_val = i * xInterval;
        double x_to_val = (i + 1) * xInterval;
        double y_from_val = conf.y_begin; // we create these variables, to avoid race condtions between different threads and moreover braking the data. Now, this is a thread-local variable.
        double y_to_val = conf.y_end;
        double sum = 0;
        while(x_from_val <= x_to_val)
        {
            double y0 = y_from_val;
            while(y0 <= y_to_val) {
                sum += f((2 * x_from_val + conf.step) / 2, (2 * y0 + conf.step) / 2) * conf.step* conf.step;
                y0 += conf.step;
            }
            x_from_val += conf.step;
        }
        #pragma omp critical
        result += sum;
    }
    return result;
}


int main(int argc, char *argv[]) {
    if (argc != 1 && argc != 7){
        std::cout << "Run this app either with no arguments, either with 6 arguments: x integration bounds, y integration bounds, step, number of threads" << std::endl;
        return -1;
    }
    omp_set_num_threads((argc != 1) ? std::stoi(argv[6]) : omp_get_max_threads());

    config conf;

    try{
        conf.x_begin = (argc != 1) ? std::stoi(argv[1]) : 1;
        conf.x_end = (argc != 1) ? std::stoi(argv[2]) : 1;
        conf.y_begin = (argc != 1) ? std::stoi(argv[3]) : 0;
        conf.y_end = (argc != 1) ? std::stoi(argv[4]) : 1;
        conf.step = (argc != 1) ? std::stod(argv[5]) : 0.001;
    } catch (...){
        std::cout << "You entered bad arguments. Try again." << std::endl;
        return -1;
    }

    double result;

    auto start_time = get_current_time_fenced();

    result = integrate(conf);

    auto end_time = get_current_time_fenced();

    std::cout << "The result is: " << result << std::endl;
    std::cout << "Time used: " << to_ms(end_time - start_time) << " milliseconds" << std::endl;
    std::cout << "Threads used: " << omp_get_max_threads() << std::endl;

    int fd_out = open("out.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(fd_out, STDOUT_FILENO);
    close(fd_out);


    std::cout << "The result is: " << result << std::endl;
    std::cout << "Time used: " << to_ms(end_time - start_time) << " milliseconds" << std::endl;
    std::cout << "Threads used: " << omp_get_max_threads() << std::endl;
    return 0;
}