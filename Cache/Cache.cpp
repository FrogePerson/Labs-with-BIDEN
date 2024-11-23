#include <iostream>
#include <ctime>

const int MASS_MAX = 1572864;

class Experement {
public:
    Experement(int massSize) {
        _mass=new int[MASS_MAX];
        _massSize = massSize;
    }
    ~Experement() {
        delete[] _mass;
    }

    void massFullPut() {
        for (int i = 0; i < _massSize; i++)
        {
            _mass[i] = std::rand();
        }
    }

    int massGet(int i) {
        if ((i < _massSize) &&(i>-1))
        {
            return _mass[i];
       }
    }
    void massPrint() {
        for (int i = 0; i < _massSize; i++)
        {
            std::cout << _mass[i] << std::endl;
        }
    }
    void runOnMass1(int size, int step) {
        int k = 0;
        for (int i = 0; i < size; i += step)
        {
            k = _mass[i];
        }
        double start = clock();
        for (int j = 0; j < 10000; j++)
        {
            for (int i = 0; i < size; i += step)
            {
                k = _mass[i];
            }
        }
        
        double end = clock();
        double time = ((end - start) / CLOCKS_PER_SEC);
        std::cout.precision(20);
        std::cout << "duration: " << time << std::endl;
           
    }
    void runOnMass2(int size, int step) {
        int k = 0;
        for (int i = size; i > -1; i -= step)
        {
            k = _mass[i];
        }
        double start = clock();
        for (int j = 0; j < 10000; j++)
        {
            for (int i = size; i > -1; i -= step)
            {
                k = _mass[i];
            }
        }

        double end = clock();
        double time = ((end - start) / CLOCKS_PER_SEC);
        std::cout.precision(20);
        std::cout << "duration: " << time << std::endl;
        
    }
    void runOnMass3(int size, int step) {
        int k = 0;
        int nuberOfSteps = size / step;
        int order[MASS_MAX];
        for (int i = 0; i < nuberOfSteps; i++)
        {
            float randFloat = rand() % (nuberOfSteps + 1);
            order[i] = rint(randFloat);
        }
        for (int i = 0; i < nuberOfSteps; i++)
        {
            k = _mass[order[i]];
        }
        double start = clock();
        for (int j = 0; j < 10000; j++)
        {
            for (int i = 0; i < nuberOfSteps; i++)
            {
                k = _mass[order[i]];
            }
        }

        double end = clock();
        double time = ((end - start) / CLOCKS_PER_SEC);
        std::cout.precision(20);
        std::cout << "duration: " << time << std::endl;
        
    }

    void ExpStart() {
        massFullPut();

        std::cout << "travel_order: direction" << std::endl;
        std::cout << " experiments number 1:" << std::endl;
        std::cout << " buffer_size: 64kb:" << std::endl;
        runOnMass1(16384, 16);

        std::cout << " experiments number 2:" << std::endl;
        std::cout << " buffer_size: 256kb:" << std::endl;
        runOnMass1(65536, 16);

        std::cout << " experiments number 3:" << std::endl;
        std::cout << " buffer_size: 1mb:" << std::endl;
        runOnMass1(262144, 16);

        std::cout << " experiments number 4:" << std::endl;
        std::cout << " buffer_size: 6mb:" << std::endl;
        runOnMass1(1572864, 16);

        //2
        std::cout << "travel_order: reverse" << std::endl;
        std::cout << " experiments number 1:" << std::endl;
        std::cout << " buffer_size: 64kb:" << std::endl;
        runOnMass2(16384, 16);

        std::cout << " experiments number 2:" << std::endl;
        std::cout << " buffer_size: 256kb:" << std::endl;
        runOnMass2(65536, 16);

        std::cout << " experiments number 3:" << std::endl;
        std::cout << " buffer_size: 1mb:" << std::endl;
        runOnMass2(262144, 16);

        std::cout << " experiments number 4:" << std::endl;
        std::cout << " buffer_size: 6mb:" << std::endl;
        runOnMass2(1572864, 16);

        //3
        std::cout << "travel_order: reverse" << std::endl;
        std::cout << " experiments number 1:" << std::endl;
        std::cout << " buffer_size: 64kb:" << std::endl;
        runOnMass3(16384, 16);

        std::cout << " experiments number 2:" << std::endl;
        std::cout << " buffer_size: 256kb:" << std::endl;
        runOnMass3(65536, 16);

        std::cout << " experiments number 3:" << std::endl;
        std::cout << " buffer_size: 1mb:" << std::endl;
        runOnMass3(262144, 16);

        std::cout << " experiments number 4:" << std::endl;
        std::cout << " buffer_size: 6mb:" << std::endl;
        runOnMass3(1572864, 16);


    }

private:
   int _massSize;
   int* _mass;

};

int main()
{
    Experement Exp1(MASS_MAX);
    Exp1.ExpStart();
    //new int Mass[MASS_MAX];
}

