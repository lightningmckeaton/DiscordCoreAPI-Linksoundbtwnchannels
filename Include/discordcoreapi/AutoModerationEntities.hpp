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
/// AutoModerationEntities.hpp - Header for the Auto-Moderation related classes and structs.
/// Jun 17, 2022 Chris M.
/// https://discordcoreapi.com
/// \file AutoModerationEntities.hpp

#pragma once

#include <discordcoreapi/FoundationEntities.hpp>
#include <discordcoreapi/CoRoutine.hpp>
#include <discordcoreapi/Https.hpp>

namespace DiscordCoreAPI {

	/**
	 * \addtogroup foundation_entities
	 * @{
	 */

	/// \brief For listing all of the auto-moderation-rules for a particular Guild .
	struct DiscordCoreAPI_Dll ListAutoModerationRulesForGuildData {
		Snowflake guildId{};///< The id of the Guild for which you would like to list the auto-moderation rules.
	};

	/// \brief For collecting an auto-moderation-rule for a particular AutoModerationRule.
	struct DiscordCoreAPI_Dll GetAutoModerationRuleData {
		uint64_t autoModerationRuleId{};///< The id of the auto-moderation-rule you would like to collect.
		Snowflake guildId{};///< The id of the Guild from which you would like to collect the auto-moderation-rule from.
	};

	/// \brief For creating an auto-moderation-rule.
	struct DiscordCoreAPI_Dll CreateAutoModerationRuleData {
		std::vector<uint64_t> exemptChannels{};///< The channel ids that should not be affected by the rule(Maximum of 50).
		std::vector<uint64_t> exemptRoles{};///< The role ids that should not be affected by the rule(Maximum of 20).
		TriggerMetaData triggerMetadata{};///< The trigger metadata.
		std::vector<ActionData> actions{};///< The actions which will execute when the rule is triggered
		TriggerType triggerType{};///< The trigger type.
		EventType eventType{};///< The event type.
		Snowflake guildId{};///< The Guild within which to create the AutoModerationRule.
		std::string name{};///< The rule name.
		bool enabled{};///< Whether the rule is enabled(False by default).

		operator Jsonifier();
	};

	/// \brief For modifying an auto-moderation-rule.
	struct DiscordCoreAPI_Dll ModifyAutoModerationRuleData {
		std::vector<uint64_t> exemptChannels{};///< The channel ids that should not be affected by the rule(Maximum of 50).
		std::vector<uint64_t> exemptRoles{};///< The role ids that should not be affected by the rule(Maximum of 20).
		TriggerMetaData triggerMetadata{};///< The trigger metadata.
		std::vector<ActionData> actions{};///< The actions which will execute when the rule is triggered
		uint64_t autoModerationRuleId{};///< The id of the auto-moderation-rule you would like to modify.
		EventType eventType{};///< The event type.
		Snowflake guildId{};///< The AutoModerationRule within which to modify the auto-moderation-rule.
		std::string name{};///< The rule name.
		bool enabled{};///< Whether the rule is enabled(False by default).

		operator Jsonifier();
	};

	/// \brief For when an auto-moderation-rule is executed.
	struct DiscordCoreAPI_Dll AutoModerationActionExecutionEventData {
		Snowflake alertSystemMessageId{};///< The id of any system auto moderation messages posted as a result of this action.
		TriggerType ruleTriggerType{};///< The trigger type of rule which was triggered.
		std::string matchedKeyword{};///< The word or phrase configured in the rule that triggered the rule
		std::string matchedContent{};///< The substring in content that triggered the rule.
		std::string content{};///< The user generated text content.
		Snowflake channelId{};///< The id of the channel in which user content was posted.
		Snowflake messageId{};///< The id of any user message which content belongs to.
		ActionData action{};///< The action which was executed.
		Snowflake guildId{};///< The id of the guild in which action was executed.
		Snowflake ruleId{};///< The id of the rule which action belongs to.
		Snowflake userId{};///< The id of the user which generated the content which triggered the rule.

		AutoModerationActionExecutionEventData() noexcept = default;

		AutoModerationActionExecutionEventData(simdjson::ondemand::value jsonObjectData);

		virtual ~AutoModerationActionExecutionEventData() noexcept = default;
	};

	/// \brief For deleting an auto-moderation-rule.
	struct DiscordCoreAPI_Dll DeleteAutoModerationRuleData {
		uint64_t autoModerationRuleId{};///< The id of the auto-moderation-rule you would like to delete.
		Snowflake guildId{};///< Guild within which to delete the auto-moderation-rule.
	};

	/// \brief Represents an auto-moderation-rule.
	class DiscordCoreAPI_Dll AutoModerationRule : public AutoModerationRuleData {
	  public:
		AutoModerationRule() noexcept = default;

		AutoModerationRule(simdjson::ondemand::value jsonObjectData);

		virtual ~AutoModerationRule() noexcept = default;
	};

	class DiscordCoreAPI_Dll AutoModerationRuleVector {
	  public:
		AutoModerationRuleVector() noexcept = default;

		operator std::vector<AutoModerationRule>();

		AutoModerationRuleVector(simdjson::ondemand::value jsonObjectData);

		virtual ~AutoModerationRuleVector() noexcept = default;

	  protected:
		std::vector<AutoModerationRule> theAutoModerationRules{};
	};

	/**@}*/

	/**
	 * \addtogroup main_endpoints
	 * @{
	 */
	/// \brief An interface class for the AutoModerationRule related Discord endpoints.
	class DiscordCoreAPI_Dll AutoModerationRules {
	  public:
		static void initialize(DiscordCoreInternal::HttpsClient*);

		/// \brief Get all of the Guild's Auto-Moderation-Rules.
		/// \returns A CoRoutine containing a vector<AutoModerationRule>.
		CoRoutine<std::vector<AutoModerationRule>> listAutoModerationRulesForGuildAsync(ListAutoModerationRulesForGuildData dataPackage);

		/// \brief Get a particular Auto-Moderation-Rule
		/// \returns A CoRoutine containing a AutoModerationRule.
		CoRoutine<AutoModerationRule> getAutoModerationRuleAsync(GetAutoModerationRuleData dataPackage);

		/// \brief Create a particular Auto-Moderation-Rule
		/// \returns A CoRoutine containing a AutoModerationRule.
		CoRoutine<AutoModerationRule> createAutoModerationRuleAsync(CreateAutoModerationRuleData dataPackage);

		/// \brief Modify a particular Auto-Moderation-Rule
		/// \returns A CoRoutine containing a AutoModerationRule.
		CoRoutine<AutoModerationRule> modifyAutoModerationRuleAsync(ModifyAutoModerationRuleData dataPackage);

		/// \brief Delete a particular Auto-Moderation-Rule
		/// \returns A CoRoutine containing a void.
		CoRoutine<void> deleteAutoModerationRuleAsync(DeleteAutoModerationRuleData dataPackage);

	  protected:
		static DiscordCoreInternal::HttpsClient* httpsClient;
	};

	/**@}*/

}// namespace DiscordCoreInternal
