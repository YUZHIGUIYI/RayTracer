//
// Created by ZZK on 2022/12/5.
//

#include <string>
#include <iostream>
#include <OneWeekend/Renderer.h>

int main(int argc, char* argv[])
{
    OneWeekend::Renderer renderer(1000, 500, 100);
    if (argc < 2)
    {
        std::cerr << "Default Renderer\n";
        renderer.run();
    } else
    {
        try
        {
            int threads = std::stoi(argv[1]);
            std::cerr << "Multithreading Renderer\n";
            std::cerr << "Current number of threads: " << threads << '\n';
            renderer.run_multithreading(threads);
        } catch (const std::invalid_argument& e)
        {
            std::cout << "Invalid argument: " << e.what() << std::endl;
        } catch (const std::out_of_range& e)
        {
            std::cout << "Out of range: " << e.what() << std::endl;
        }
    }
}





















