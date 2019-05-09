
// hashindex neemt een T-sleutel en geeft een hashwaarde tussen 0 en n terug.

#include <list>
#include <vector>

using std::list;
using std::vector;

template <class T, int (*hashindex)(const T &, int n)>
class Hashtabel : public vector<list<T> > {
   public:
    Hashtabel(int grootteTabel) : grootteTabel{grootteTabel} {
        this->resize(grootteTabel);
    };

    void vul(vector<T> &v) {
        for (auto sleutel : v) {
            int index = hashindex(sleutel, this->grootteTabel);
            (*this)[index].emplace_back(sleutel);
        }
    }

    double score() {
        double score = 0;
        for (int i = 0; i < this->size(); i++) {
            score += (*this)[i].size() * (*this)[i].size();
        }

        score = ( 1.0 / ((double)this->size()) ) * ( ((double)this->size()) + 0.5 * score);
        return score;
    }

   private:
    int grootteTabel;
};
