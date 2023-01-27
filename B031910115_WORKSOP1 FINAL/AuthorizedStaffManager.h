#ifndef AUTHORIZEDSTAFFMANAGER_H
#define AUTHORIZEDSTAFFMANAGER_H

class AuthorizedStaffManager
{
public:
	int registerStaff(AuthorizedStaff* staff);
	bool loginStaff(AuthorizedStaff* staff);

	AuthorizedStaff* staffInformation(string staffID);

	int updatePassword(AuthorizedStaff* staff);
	int updatePhone(AuthorizedStaff* staff);
};

#endif 

