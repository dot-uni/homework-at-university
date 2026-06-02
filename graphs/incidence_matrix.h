#ifndef INC_MATRIX
#define INC_MATRIX

class IncidenceMatrix
{   
    size_t vcount_, ecount_;
    int** matrix_;
    public:
        IncidenceMatrix() : vcount_(0), ecount_(0) ,matrix_(nullptr) {}
        ~IncidenceMatrix() { delete_matrix(); }
    public:
        bool LoadIncMatrix(const std::string& file_name);
        void Print() const;
        void BreadthFirstSearch(size_t start) const;
        void DepthFirstSearch(size_t start) const;
        void Dijkstra(size_t start, int* dist, size_t* parent) const;
    private:
        void delete_matrix();
};

#endif 