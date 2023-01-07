/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:27:00 by ddecourt          #+#    #+#             */
/*   Updated: 2023/01/07 16:18:29 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

//NEED TO FINISH PRIVMSG BY DOING PROPER PARSING cf RFC doc

void Command::privmsg(Message *msg, std::vector<std::string> message)
{
    (void)msg;
    //(void)message;

    
    Channel *channel;
    User *user = msg->getuser();
    Server *server = msg->getserver();
    
    std::vector<std::string>::iterator it;
    std::vector<std::string>::iterator it2;
    std::vector<std::string> channels_names = server->get_all_channels_names();
    std::string channel_name;
    std::string buffer;

    if (message.size() != 3)
    {
        if (message.size() >= 2)
            return(send_reply(user->getFd(), user->getPrefix() + " 404 " + ERR_NOSUCHCHANNEL(message[1])));
        return (send_reply(user->getFd(), ERR_UNKNOWNCOMMAND("PRIVMSG without arg")));
    }
    for (it = message.begin(); it != message.end(); it++)
    {
        for(it2 = channels_names.begin(); it2 != channels_names.end(); it2++)
        {
            if ((*it).find(*it2) != std::string::npos)
            {
                channel_name = (*it).substr(0, (*it2).length());
                (*it).erase(0, ((*it2).length() + 1));
                channel = server->get_channel_by_name(channel_name);
                //:diane!diane@localhost PRIVMSG #lolo :Bonjour
            }
        }
        if (it != message.begin())
            buffer += (*it) + " ";
    }
    buffer.erase(0, 2);
    channel->broadcast_msg(user->getPrefix() + " PRIVMSG " + channel_name + " " + buffer + END, user);
    //std::cout << RED << "==> [PRIVMSG] " << BLUE << user->getNickname() << " send a message in channel " << channel->getName() << DEFAULT << std::endl;
}