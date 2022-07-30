#include"protection.hpp"
#include"CNetGamePlayer.hpp"
constexpr auto Block_Time = 60000;
namespace big::protection
{
	struct Player
	{
		ULONGLONG block_time;
		Player(int64_t user_id) :block_time(0)
		{
		}
	};
	std::unordered_map <int64_t, Player*> Players;
	void checkPlayerExist(CNetGamePlayer* src)
	{
		if (src != nullptr)
		{
			int64_t user_id = src->get_net_data()->m_rockstar_id;
			if (Players.find(user_id) == Players.end()) Players[user_id] = new Player(user_id);
		}
	}
	bool isBlock(CNetGamePlayer* src)
	{
		checkPlayerExist(src);
		int64_t user_id = src->get_net_data()->m_rockstar_id;
		//������ֹʱ���Ƿ���ڵ�ǰʱ��
		return GetTickCount64() < Players[user_id]->block_time;
	}
	void setBlock(CNetGamePlayer* src)
	{
		checkPlayerExist(src);
		int64_t user_id = src->get_net_data()->m_rockstar_id;
		//����ֹʱ������Ϊ��ǰʱ��+60s
		Players[user_id]->block_time = GetTickCount64() + Block_Time;
	}
}