/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codes.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:01:01 by anshovah          #+#    #+#             */
/*   Updated: 2024/05/04 03:52:33 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODES_HPP
#define CODES_HPP

#define ERR_UNKNOWNCOMMAND      "421"     // "<command> :Unknown command"
#define ERR_NORECIPIENT         "411"     // ":No recipient given (<command>)"
#define ERR_NOTEXTTOSEND        "412"     // ":No text to send"
#define ERR_NOSUCHNICK          "401"     // "<nickname>	:No such nick/channel"



// EVERYTHING BELOW IS NOT USED YET
// -----------------------------------------------------------------------------



// privmsg


#define ERR_TOOMANYTARGETS      407     // "<target> :Duplicate recipients. No message delivered"

// invite
#define ERR_NEEDMOREPARAMS      461     // "<command> :Not enough parameters"

#define RPL_INVITING            341     // "<channel> <nick>"
#define RPL_CHANNELMODEIS       324     // "<channel> <mode> <mode params>"
#define ERR_CANNOTSENDTOCHAN    404     // "<channel name> :Cannot send to channel"
#define RPL_TOPIC               332		// "<channel>	:<topic>"
#define ERR_NOSUCHCHANNEL       403     // "<channel name> :No such channel"



#define ERR_USERONCHANNEL       443     // "<user> <channel> :is already on channel"

// mode
#define ERR_UNKNOWNMODE         472     // "<char> :is unknown mode char to me"
#define ERR_USERSDONTMATCH      502     // ":Cant change mode for other users"
#define ERR_UMODEUNKNOWNFLAG    501     // ":Unknown MODE flag"
#define RPL_UMODEIS             221     // "<user mode string>"

// kick N join 
#define ERR_BADCHANMASK         476   	// "<channel>	:Bad Channel Mask"
#define ERR_INVITEONLYCHAN      473   	// "<channel>	:Cannot join channel (+i)"
#define ERR_CHANNELISFULL       471   	// "<channel>	:Cannot join channel (+l)"
#define ERR_BANNEDFROMCHAN      474   	// "<channel>	:Cannot join channel (+b)"
#define ERR_BADCHANNELKEY       475   	// "<channel>	:Cannot join channel (+k)"
#define ERR_KEYSET              467		// "<channel>	:Channel key already set"
#define ERR_NOTONCHANNEL        442		// "<channel> 	:You're not on that channel"
#define ERR_CHANOPRIVSNEEDED    482     // "<channel> 	:You're not channel operator"
#define RPL_NOTOPIC             331  	//"<channel>	:No topic is set"

// composeChnlMsg(int number, msg)


// topic
#define ERR_NONICKNAMEGIVEN     431      // ":No nickname given"
#define ERR_NOSUCHSERVER        402      // "<server name> :No such server"

// whois
#define RPL_AWAY                301     // "<nick> 		:<away message>"
#define RPL_WHOISCHANNELS       319     // "<nick> 		:{[@|+]<channel><space>}"
#define RPL_ENDOFWHOIS          318     // "<nick> 		:End of /WHOIS list"
#define RPL_WHOISOPERATOR       313     // "<nick> 		:is an IRC operator"


#define RPL_WHOISUSER           311		// "<nick> <user> <host> * :<real name>"
#define RPL_WHOISIDLE           317     // "<nick> <integer> :seconds idle"
#define RPL_WHOISSERVER         312     // "<nick> <server> :<server info>"



// ALL OF THEM
// privmsg
// #define ERR_NORECIPIENT         411     // ":No recipient given (<command>)"
// #define ERR_CANNOTSENDTOCHAN    404     // "<channel name> :Cannot send to channel"
// #define ERR_WILDTOPLEVEL        414     // "<mask> :Wildcard in toplevel domain"
// #define ERR_NOSUCHNICK          401     // "<nickname> :No such nick/channel"
// #define RPL_AWAY                301     // "<nick> :<away message>"
// #define ERR_NOTEXTTOSEND        412     // ":No text to send"
// #define ERR_NOTOPLEVEL          413     // "<mask> :No toplevel domain specified"
// #define ERR_TOOMANYTARGETS      407     // "<target> :Duplicate recipients. No message delivered"

// // invite
// #define ERR_NEEDMOREPARAMS      461     // "<command> :Not enough parameters"
// #define ERR_NOTONCHANNEL        442     // "<channel> :You're not on that channel"
// #define ERR_CHANOPRIVSNEEDED    482     // "<channel> :You're not channel operator"
// #define RPL_INVITING            341     // "<channel> <nick>"
// #define ERR_USERONCHANNEL       443     // "<user> <channel> :is already on channel"

// // mode
// #define ERR_NEEDMOREPARAMS      461     // "<command> :Not enough parameters"
// #define ERR_CHANOPRIVSNEEDED    482     // "<channel> :You're not channel operator"
// #define ERR_NOTONCHANNEL        442     // "<channel> :You're not on that channel"
// #define RPL_BANLIST             367     // "<channel> <banid>"
// #define ERR_UNKNOWNMODE         472     // "<char> :is unknown mode char to me"
// #define ERR_USERSDONTMATCH      502     // ":Cant change mode for other users"
// #define ERR_UMODEUNKNOWNFLAG    501     // ":Unknown MODE flag"
// #define RPL_CHANNELMODEIS       324     // "<channel> <mode> <mode params>"
// #define ERR_KEYSET              467     // "<channel> :Channel key already set"
// #define RPL_ENDOFBANLIST        368     //  "<channel> :End of channel ban list"
// #define ERR_NOSUCHCHANNEL       403     // "<channel name> :No such channel"
// #define RPL_UMODEIS             221     // "<user mode string>"

// // kick N join 
// #define ERR_BADCHANMASK         476      // "<channel> :Bad Channel Mask"
// #define ERR_INVITEONLYCHAN      473      // "<channel> :Cannot join channel (+i)"
// #define ERR_CHANNELISFULL       471      // "<channel> :Cannot join channel (+l)"
// #define RPL_TOPIC               332      // "<channel> :<topic>"
// #define ERR_BANNEDFROMCHAN      474      // "<channel> :Cannot join channel (+b)"
// #define ERR_BADCHANNELKEY       475      // "<channel> :Cannot join channel (+k)"
// #define ERR_TOOMANYCHANNELS     405      // "<channel name> :You have joined too many channels"

// // topic
// #define RPL_NOTOPIC             331      //"<channel> :No topic is set"

// // whois
// #define ERR_NOSUCHSERVER        402      // "<server name> :No such server"
// #define RPL_WHOISUSER           311      // "<nick> <user> <host> * :<real name>"
// #define RPL_WHOISCHANNELS       319      // "<nick> :{[@|+]<channel><space>}"
// #define RPL_WHOISIDLE           317      // "<nick> <integer> :seconds idle"
// #define RPL_ENDOFWHOIS          318      // "<nick> :End of /WHOIS list"
// #define ERR_NONICKNAMEGIVEN     431      // ":No nickname given"
// #define RPL_WHOISSERVER         312      // "<nick> <server> :<server info>"
// #define RPL_WHOISOPERATOR       313      // "<nick> :is an IRC operator"

#endif