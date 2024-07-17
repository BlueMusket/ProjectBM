#pragma once

class CQueryBuilder;
class CDBConnection
{
public:
	CDBConnection();
	~CDBConnection();

public:
	bool Connect();
	void DisConnect();

public:
	bool SendQuery(CQueryBuilder& query);

private:
};

