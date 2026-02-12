/*******************************************************************************
 * util/WikiTokenWaiter.h                                                      *
 *                                                                             *
 * Copyright (C) 2024 RetroShare Team <retroshare.project@gmail.com>           *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU Affero General Public License as              *
 * published by the Free Software Foundation, either version 3 of the          *
 * License, or (at your option) any later version.                             *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU Affero General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Affero General Public License    *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                             *
 *******************************************************************************/

#pragma once

#include <chrono>
#include <thread>
#include <functional>
#include <retroshare/rstokenservice.h>

/**
 * @brief Utility class for waiting on GXS token completion
 * 
 * This class provides a static helper method to block and wait for a token
 * request to complete, checking the status periodically.
 */
class WikiTokenWaiter
{
public:
	/**
	 * @brief Wait for a token to complete
	 * 
	 * Blocks the calling thread while waiting for a token request to complete.
	 * Polls the token status periodically until it reaches a final state
	 * (COMPLETE or FAILED) or times out.
	 * 
	 * @param statusChecker Function that takes a token and returns its current status
	 * @param token The token to wait for
	 * @param maxWait Maximum time to wait in milliseconds (default: 10000ms)
	 * @param checkEvery Time between status checks in milliseconds (default: 20ms)
	 * @return true if the token completed successfully (COMPLETE), false otherwise
	 */
	static bool waitForToken(
		std::function<RsTokenService::GxsRequestStatus(uint32_t)> statusChecker,
		uint32_t token,
		std::chrono::milliseconds maxWait = std::chrono::milliseconds(10000),
		std::chrono::milliseconds checkEvery = std::chrono::milliseconds(20))
	{
		auto timeout = std::chrono::steady_clock::now() + maxWait;
		auto st = statusChecker(token);
		
		while (!(st == RsTokenService::FAILED || st >= RsTokenService::COMPLETE) 
		       && std::chrono::steady_clock::now() < timeout)
		{
			std::this_thread::sleep_for(checkEvery);
			st = statusChecker(token);
		}
		
		return st == RsTokenService::COMPLETE;
	}
};
