#ifndef	GOODSMANAGER_H
#define GOODSMANAGER_H

class GoodsManager
{
public:
	int insertGoods(Goods* goods);
	int updateGoods(Goods* goods);
	int deleteGoods(Goods* goods);

	Goods* displayGoods();
	Goods* selectGoods(int goodsID);

	Goods* searchGoodsName(string goodsName);

	void updateQuantity(int purchaseGoodsID);
};

#endif 


