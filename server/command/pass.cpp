/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:58:09 by ddecourt          #+#    #+#             */
/*   Updated: 2022/12/09 13:57:02 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void Command::pass(Message *msg, std::vector<std::string> message)
{
    User *user = msg->getuser();
    // (void)message;
    if (message.size() == 1)
        return(send_reply(user->getFd(), ERR_NEEDMOREPARAMS(message[0])));
    if (message[1] != PASSWORD)
        return(send_reply(user->getFd(), ERR_PASSWDMISMATCH()));
    if (message[1] == PASSWORD)
        user->setisPassword(true);
}
