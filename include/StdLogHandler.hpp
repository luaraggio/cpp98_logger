/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StdLogHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 23:03:49 by lraggio           #+#    #+#             */
/*   Updated: 2025/11/12 19:48:41 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDLOGHANDLER_HPP
# define STDLOGHANDLER_HPP

# include "Logger.hpp"

/**
 * @file StdLogHandler.hpp
 * @brief Concrete LogHandler that writes messages to standard output.
 *
 * Implements the Strategy interface `LogHandler`, formatting and
 * printing log messages to the console with level prefixes.
 */

class StdLogHandler : public LogHandler
{
  public:
	StdLogHandler();
	virtual ~StdLogHandler();

	virtual void handleDebug(t_event event);
	virtual void handleInfo(t_event event);
	virtual void handleWarning(t_event event);
	virtual void handleError(t_event event);
};

#endif
