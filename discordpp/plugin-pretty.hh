#pragma once

namespace discordpp{
	// https://discord.com/developers/docs/topics/gateway#activity-object-activity-flags
	struct ActivityFlags{
		bool active = true;

		// TODO
		json toJson(){
			return json();
		}
	};

	// https://discord.com/developers/docs/topics/gateway#activity-object-activity-secrets
	struct ActivitySecrets{
		bool active = true;

		// TODO
		json toJson(){
			return json();
		}
	};


	// https://discord.com/developers/docs/topics/gateway#activity-object-activity-assets
	struct ActivityAssets{
		bool active = true;

		// TODO
		json toJson(){
			return json();
		}
	};

	// https://discord.com/developers/docs/topics/gateway#activity-object-activity-party
	struct ActivityParty{
		bool active = true;

		// TODO
		json toJson(){
			return json();
		}
	};

	// https://discord.com/developers/docs/topics/gateway#activity-object-activity-emoji
	struct ActivityEmoji{
		bool active = true;

		// TODO
		json toJson(){
			return json();
		}
	};

	// https://discord.com/developers/docs/topics/gateway#activity-object-activity-timestamps
	struct ActivityTimestamps{
		bool active = true;

		// TODO
		json toJson(){
			return json();
		}
	};

	// https://discord.com/developers/docs/topics/gateway#activity-object
	struct Activity{
		bool active = true;

		std::string name;
		enum type{
			Game, Streaming, Listening, Custom
		}type = Game;
		std::string url;
		std::time_t created_at = std::numeric_limits<std::time_t>::max();
		ActivityTimestamps timestamps;
		snowflake application_id = std::numeric_limits<snowflake>::max();
		std::string details;
		std::string state;
		ActivityEmoji emoji;
		ActivityParty party;
		ActivityAssets assets;
		ActivitySecrets secrets;
		enum instance{
			low, high, undefined
		}instance = undefined;
		ActivityFlags flags;

		Activity(){
			timestamps.active = false;
			emoji.active = false;
			party.active = false;
			assets.active = false;
			secrets.active = false;
			flags.active = false;
		}

		json toJson(){
			json out{
					{"name", name},
					{"type", type}
			};
			if(!url.empty()){
				out["url"] = url;
			}
			if(created_at != std::numeric_limits<std::time_t>::max()){
				out["created_at"] = (int)created_at;
			}
			if(timestamps.active){
				out["timestamps"] = timestamps.toJson();
			}
			if(application_id != std::numeric_limits<snowflake>::max()){
				out["application_id"] = application_id;
			}
			if(!details.empty()){
				out["details"] = details;
			}
			if(!state.empty()){
				out["state"] = state;
			}
			if(emoji.active){
				out["emoji"] = emoji.toJson();
			}
			if(party.active){
				out["party"] = party.toJson();
			}
			if(assets.active){
				out["assets"] = assets.toJson();
			}
			if(secrets.active){
				out["secrets"] = secrets.toJson();
			}
			if(instance != undefined){
				out["instance"] = (bool)instance;
			}
			if(flags.active){
				out["flags"] = flags.toJson();
			}
			return out;
		}
	};

	// https://discord.com/developers/docs/topics/gateway#update-status
	struct Status{
		int since = -1;
		Activity game;
		enum status{
			online, dnd, idle, invisible, offline
		}status = online;
		bool afk = false;

		Status(){
			game.active = false;
		}

		json toJson(){
			json out;
			if(since >= 0){
				out["since"] = since;
			}
			if(game.active){
				out["game"] = game.toJson();
			}
			switch(status){
				case online:
					out["status"] = "online";
					break;
				case dnd:
					out["status"] = "dnd";
					break;
				case idle:
					out["status"] = "idle";
					break;
				case invisible:
					out["status"] = "invisible";
					break;
				case offline:
					out["status"] = "offline";
					break;
			}
			out["afk"] = afk;
			return out;
		}
	};

	template<class BASE>
	class PluginPretty: public BASE, virtual BotStruct{
	public:
		virtual void sendMessage(
				const snowflake &channel,
				const std::string &message,
				const std::function<void(json)> &callback = [](const json &){}
		){
			std::ostringstream target;
			target << "/channels/" << channel << "/messages";
			BASE::call("POST", target.str(), json({{"content", message}}));
			call(
					std::make_shared<std::string>("POST"),
					std::make_shared<std::string>(target.str()),
					std::make_shared<void(json)>(callback)
			);
		}

		virtual void setStatus(
				const Status &status,
				const std::function<void()> &callback = [](){}
		){
			send(
					3,
					std::make_shared<json>(status),
					std::make_shared<std::function<void()>>(callback)
			);
		}
	};
}