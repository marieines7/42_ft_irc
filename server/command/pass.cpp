/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:58:09 by ddecourt          #+#    #+#             */
/*   Updated: 2023/01/07 15:31:47 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void Command::pass(Message *msg, std::vector<std::string> message)
{
    User *user = msg->getuser();
    Server *server = msg->getserver();
    std::string serverPassword = server->getPassword();

    if (message.size() == 1)
        return(send_reply(user->getFd(), ERR_NEEDMOREPARAMS(message[0])));
    if (message[1] != serverPassword)
    {
        user->setisOnline(false);
        return(send_reply(user->getFd(), user->getPrefix() + " 462 " + ERR_PASSWDMISMATCH()));
    }
    if (message[1] == serverPassword)
        user->setisPassword(true);
}
