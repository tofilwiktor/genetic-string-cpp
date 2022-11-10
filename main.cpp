#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct Text {
    std::string text;
    int Fitness;
};

const int pop_size = 1000;
const int mutationRate = 25;

class Population {
    public:
        Population(std::string res) : result(res) {}
        ~Population() {}
        std::pair<Text, Text> getFittest() {
            return std::make_pair(pop.at(0), pop.at(1));
        }

        void calculateFitness() {
            for (auto& x : pop) {
                int fitness = 0;
                for (int i = 0; i < x.text.length(); i++)
                    if (x.text.at(i) == result.at(i))
                        fitness++;
                x.Fitness = fitness;
            }
        }

        void mutation(Text& t) {
            char randomChar = rand() % 255; 
            int mutPos = rand() % t.text.length();
            t.text.at(mutPos) = randomChar;

        }

        void mating() {
            for (int i = 0; i < pop.size(); i++) {
                for (int j = 0; j < pop.at(i).text.length(); j++) {
                    int temp = rand() % 2;
                    pop.at(i).text.at(j) = pop.at(temp).text.at(j);
                    if (rand() % 1000 < mutationRate) mutation(pop.at(i));
                }
            }
        }

        void sorted() {
            std::sort(pop.begin(), pop.end(), [](Text a, Text b) { return a.Fitness > b.Fitness; } );
        }

        void init(int pop_size) {

            for (int i = 0; i < pop_size; i++) {
                Text individual;
                for (int j = 0; j < result.length(); j++) {
                    char a = rand() % 255;
                    individual.text += a;
                }
                pop.push_back(individual);
            }
        }

        bool isFinished() {
            if (pop.at(0).text == result) return true;
            return false;
        }

        private:
            std::vector <Text> pop;
            std::string result;
};

int main () {
    srand(time(NULL));
    
    const std::string res = "this is a test";
    Population population(res);

    population.init(pop_size);

    int count = 0;
    

    while(!population.isFinished()) {
        population.mating();
        population.calculateFitness();
        population.sorted();

        std::cout << "Generation: " << count << " best result: " <<
        population.getFittest().first.text << " " << population.getFittest().second.text
        << std::endl;

        count++;
    }

    return EXIT_SUCCESS;
}
