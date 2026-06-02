#ifndef ADJ_LIST
#define ADJ_LIST

struct EdgeNode
{
    int to;
    int weight;
    EdgeNode* next;
};

class AdjList
{
    int size_;
    EdgeNode** list_;
    public:
        AdjList() : size_(0), list_(nullptr) {}
        ~AdjList() { delete_list(); }
        bool LoadAdjList(const std::string& file_name);
        void BreadthFirstSearch(int start) const;
        void DepthFirstSearch(int start) const;
        void Dijkstra(int start, int* dist, int* parent) const;
        void Print() const;
    private:
        void delete_list();
};

#endif 