class Ponto2D{
    private:
        int x,y;   
    
    public:
        Ponto2D(int xx=0, int yy=0): x(xx), y(yy) {};
        Ponto2D& operator-- ();
        Ponto2D operator+ (const Ponto2D&) const;
        ~Ponto2D(){};
        
        int getX();
        int getY();
};