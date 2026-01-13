#ifndef SV_SVBESTFRIENDLIST_HPP
#define SV_SVBESTFRIENDLIST_HPP

struct SvBestFriendList
{
	static SvBestFriendList* Get();

	bool HasFriend() const;
};

#endif
