#include <lsys/machinedesc/Parser.hpp>
#include <lsys/Machine.hpp>

#include <cstdlib>
#include <iostream>

struct PSTracer : public lsys::Trace
{
    PSTracer(double dx, double dy)
    : dx_(dx), dy_(dy), first_(true), count_(0)
    {
        std::cout << "%!PS-Adobe-2.1\n\n0.1 setlinewidth\nnewpath\n";
    }
    
    virtual ~PSTracer()
    {
        std::cout << "stroke\n\nshowpage\n";
    }
    
    void draw(double x0, double y0, double x1, double y1)
    {
        x0 += dx_;
        x1 += dx_;
        y0 += dy_;
        y1 += dy_;
        
        if(first_)
        {
            first_ = false;
            lastx_ = x1;
            lasty_ = y1;
        
            std::cout << x0 << ' ' << y0 << " moveto\n"
                      << x1 << ' ' << y1 << " lineto\n";
        }
        else
        {
            if(x0 != lastx_ || y0 != lasty_)
            {
                std::cout << x0 << ' ' << y0 << " moveto\n";
            }
            
            lastx_ = x1;
            lasty_ = y1;

            std::cout << x1 << ' ' << y1 << " lineto\n";
        }

        ++count_;
        
        if(count_ == 1000)
        {
            count_ = 0;
            first_ = true;
            std::cout << "stroke\n";
        }
    }

private:
    double lastx_;
    double lasty_;
    double dx_;
    double dy_;
    bool first_;
    int count_;
};

struct BoundsChecker : public lsys::Trace
{
    double minx;
    double miny;

    BoundsChecker()
    : first_(true)
    {
    }

    static inline double min(double a, double b)
    {
        return a < b ? a : b;
    }
    
    void draw(double x0, double y0, double x1, double y1)
    {
        if(first_)
        {
            minx = min(x0, x1);
            miny = min(y0, y1);

            first_ = false;
        }
        else
        {
            minx = min(minx, x0);
            minx = min(minx, x1);
            miny = min(miny, y0);
            miny = min(miny, y1);
        }
    }

private:
    bool first_;
};

void findBounds(std::string const& filename, int depth, double step,
                double& minx, double& miny)
{
    std::vector<lsys::Generator> generators;
    int mainGen;
    lsys::machinedesc::readMachineDesc(filename, generators, mainGen);
    lsys::Machine machine(generators, depth, step);
    BoundsChecker checker;
    
    machine.attachTracer(&checker);
    machine.startFrom(mainGen);

    minx = checker.minx;
    miny = checker.miny;
}
    
int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cerr << "Usage: " << argv[0] <<
            " machinefile depth initialStepLength\n";
    }
    else
    {
        const std::string filename = argv[1];
        const int depth = atoi(argv[2]);
        const double step = atof(argv[3]);
        std::vector<lsys::Generator> generators;
        int mainGen;
        
        try
        {
            lsys::machinedesc::readMachineDesc(filename, generators, mainGen);
            lsys::Machine machine(generators, depth, step);
            
            std::cerr << "%Executing machine file: " << filename << '\n'
                      << "%Initial depth: " << depth << '\n'
                      << "%Initial step length: " << step << '\n';

            double minx = 0, miny = 0;
            minx -= 10;
            miny -= 10;
            
            findBounds(filename, depth, step, minx, miny);
            
            PSTracer tracer(minx * -1.0, miny * -1.0);

            machine.attachTracer(&tracer);
            machine.startFrom(mainGen);
        }
        catch(std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << '\n';
        }
    }
}
