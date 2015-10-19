#ifndef _SESSION_H
#define _SESSION_H
class Session
{
public:
    Session();
	void set_session_id(int id)
	{
		session_id_ = id;
	}
    int session_id()
    {
        return session_id_;
    }
    void recycler( void )
    {
        bIsRecycler_=true;
    }
protected:
	int session_id_;
    bool bIsRecycler_ = true;
	
};
#endif
