 #include<vector>
struct Color{
    float red, green ,blue;
    Color();
    Color(float red,float green,float blue);
    ~Color();
};
class Image{
public:
    Image(int width,int height);

    Image();

    ~Image();
    Color GetColor(int x, int y)const;
    void SetColor(const Color& color , int x , int y);
    void Export(const char * path)const;
    void Read(const char* path);

    int getMWidth() const;
    int getMHeight() const;

private:
    int m_width;
    int m_height;
    std::vector<Color> m_colors;

};