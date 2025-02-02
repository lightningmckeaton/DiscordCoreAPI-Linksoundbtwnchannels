/*
	DiscordCoreAPI, A bot library for Discord, written in C++, and featuring explicit multithreading through the usage of custom, asynchronous C++ CoRoutines.

	Copyright 2021, 2022 Chris M. (RealTimeChris)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
	USA
*/
/// SongAPI.hpp - Header for the song api related stuff.
/// Sep 17, 2021
/// https://discordcoreapi.com
/// \file SongAPI.hpp

#pragma once

#include <discordcoreapi/FoundationEntities.hpp>
#include <discordcoreapi/EventEntities.hpp>
#include <discordcoreapi/GuildMemberEntities.hpp>
#include <discordcoreapi/VoiceConnection.hpp>

namespace DiscordCoreAPI {

	/**
	 * \addtogroup voice_connection
	 * @{
	 */
	/// \brief A class representing the Song APIs.
	class DiscordCoreAPI_Dll SongAPI {
	  public:
		friend class DiscordCoreInternal::SoundCloudAPI;
		friend class DiscordCoreInternal::YouTubeAPI;
		friend class VoiceConnection;

		DiscordCoreInternal::Event<CoRoutine<void>, SongCompletionEventData> onSongCompletionEvent{};
		UnboundedMessageBlock<AudioFrameData> audioDataBuffer{};
		DiscordCoreInternal::EventDelegateToken eventToken{};
		Playlist playlist{};

		SongAPI(const Snowflake guildId);

		/// \brief For setting up behavior in response to a completed song
		/// \param handler A delegate taking a SongCompletionEventData structure as an argument.
		/// \param guildId The id of the Guild for which you would like to instantiate this event.
		static void onSongCompletion(std::function<CoRoutine<void>(SongCompletionEventData)> handler, const Snowflake guildId);

		/// \brief Search for a Song to play.
		/// \param searchQuery The Song to search for.
		/// \param guildId The Guild id to search for the Song within.
		/// \returns A vector of Song objects representing the search results.
		static std::vector<Song> searchForSong(const std::string& searchQuery, const Snowflake guildId);

		/// \brief Adds a Song to the current Playlist's queue.
		/// \param guildMember The GuildMember that is adding the Song to the queue.
		/// \param song The Song to be added to the queue.
		/// \returns The Song that was added to the queue.
		static Song addSongToQueue(const GuildMember& guildMember, Song& song);

		/// \brief Checks to see if there are any playable Songs in the current Playlist.
		/// \param guildId The id of the Guild for which we would like to check its Playlist for Songs.
		/// \returns A bool representing whether there are any playable Songs.
		static bool isThereAnySongs(const Snowflake guildId);

		/// \brief Send the next playable song off of the current Guild's Playlist to be played.
		/// \param guildMember The GuildMember who is requesting the Song to be sent.
		/// \returns A bool suggesting the success status of the send.
		static bool sendNextSong(const GuildMember& guildMember);

		/// \brief Plays the current Song. (Assuming that you are currently connected to a VoiceConnection).
		/// \param guildId The id of the Guild within which to play the current Song.
		/// \returns A bool suggesting the success or failure of the play command.
		static bool play(const Snowflake guildId);

		/// \brief Skips to the next Song in the queue, if applicable.
		/// \param guildMember The GuildMember structure of the individual who is skipping the Song.
		static void skip(const GuildMember& guildMember);

		/// \brief Stops the currently playing Song.
		/// \param guildId The id of the Guild within which to stop the currently playing music.
		static void stop(const Snowflake guildId);

		/// \brief Toggles pausing on and off.
		/// \param guildId The id of the Guild which you would like to pause the Song for.
		static void pauseToggle(const Snowflake guildId);

		/// \brief Checks if there is currently playing music for the current Guild.
		/// \param guildId The id for the desired Guild to check the current playing status.
		/// \returns A bool representing the currently playing status.
		static bool areWeCurrentlyPlaying(const Snowflake guildId);

		/// \brief Collects the Playlist from the SongAPI.
		/// \param guildId The Guild for which to collect the Playlist from.
		/// \returns A Playlist.
		static Playlist getPlaylist(const Snowflake guildId);

		/// \brief Sets the playlist of the desired Guild.
		/// \param playlistNew The new Playlist to be set.
		/// \param guildId The id of the desired Guild to set the Playlist of.
		static void setPlaylist(const Playlist& playlistNew, const Snowflake guildId);

		/// \brief Returns the current loop-all status of the current Guild's Playlist.
		/// \param guildId The id of the Guild for which you would like to check the loop-all status of.
		/// \returns A bool representing the current loop-all status.
		static bool isLoopAllEnabled(const Snowflake guildId);

		/// \brief Enables or disables the loop-all status of the playlist.
		/// \param enabled A bool representing whether or not to enable the loop-all status.
		/// \param guildId The Guild id for which Guild to update this status in.
		static void setLoopAllStatus(bool enabled, const Snowflake guildId);

		/// \brief Returns the current loop-song of the current Guild's Playlist.
		/// \param guildId The id of the Guild for which you would like to check the loop-song status of. \returns A bool representing the current loop-song status.
		static bool isLoopSongEnabled(const Snowflake guildId);

		/// \brief Enables or disables the loop-song status of the playlist.
		/// \param enabled A bool representing whether or not to enable the loop-song status.
		/// \param guildId The Guild id for which Guild to update this status in.
		static void setLoopSongStatus(bool enabled, const Snowflake guildId);

		/// \brief Sets the position of a Song in the current Playlist's song queue.
		/// \param firstSongPosition The first Song's initial position.
		/// \param secondSongPosition The first Song's final position.
		/// \param guildId The id of the desired Guild to update the Song positions in.
		static void modifyQueue(int32_t firstSongPosition, int32_t secondSongPosition, const Snowflake guildId);

		/// \brief Collects the currently playing Song.
		/// \param guildId The id for which Guild to collect the current Song of.
		/// \returns The current Song for the given Guild.
		static Song getCurrentSong(const Snowflake guildId);

		/// \brief Sets the currently playing Song.
		/// \param song The Song to set as the currently playing Song.
		/// \param guildId The id for which Guild to set the current Song of.
		static void setCurrentSong(const Song& song, const Snowflake guildId);

		~SongAPI() noexcept = default;

	  protected:
		static std::mutex accessMutex;

		std::unique_ptr<std::jthread> taskThread{ nullptr };
		bool areWeInstantiated{};
		Snowflake guildId{};

		void sendNextSongFinal(const GuildMember& guildMember);

		void cancelCurrentSong();

		bool sendNextSong();
	};
	/**@}*/
};// namespace DiscordCoreAPI