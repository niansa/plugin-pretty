#pragma once

namespace discordpp{
    struct apiStruct {
        virtual bool isValid() const = 0;
        virtual json toJson() const = 0;
    };

    // https://discord.com/developers/docs/topics/gateway#activity-object-activity-flags
    struct ActivityFlags: public apiStruct {
        bool instance = false;
        bool join = false;
        bool spectate = false;
        bool joinRequest = false;
        bool sync = false;
        bool play = false;

        int getflags() const{
            // Create integer bitwise
            int out = 0;
            //INSTANCE
            out += instance;
            out <<= 1;
            //JOIN
            out += join;
            out <<= 1;
            //SPECTATE
            out += spectate;
            out <<= 1;
            //JOIN_REQUEST
            out += joinRequest;
            out <<= 1;
            //SYNC
            out += sync;
            out <<= 1;
            //PLAY
            out += play;
            out <<= 1;
            // Return the resulting integer
            return out;
        }
        bool isValid() const{
            return getflags();
        }
        json toJson() const{
            return json(getflags());
        }
    };

    // https://discord.com/developers/docs/topics/gateway#activity-object-activity-secrets
    struct ActivitySecrets: public apiStruct {
        std::string join; // Optional
        std::string spectate; // Optional
        std::string match; // Optional

        bool isValid() const{
            return !join.empty() || !spectate.empty() || !match.empty();
        }
		json toJson() const{
            json out;
            if (join.empty()) {
                out["join"] = join;
            }
            if (spectate.empty()) {
                out["spectate"] = spectate;
            }
            if (match.empty()) {
                out["match"] = match;
            }
            return out;
		}
	};

    // https://discord.com/developers/docs/topics/gateway#activity-object-activity-assets
    struct ActivityAssets: public apiStruct {
        snowflake large_image = 0; // Optional
        std::string large_text; // Optional
        snowflake small_image = 0; // Optional
        std::string small_text; // Optional

        bool isValid() const{
            return large_image != 0 || !large_text.empty()
                    || small_image != 0 || !small_text.empty();
        }
		json toJson() const{
            json out;
            if (large_image != 0) {
                out["large_image"] = large_image;
            }
            if (small_image != 0) {
                out["small_image"] = small_image;
            }
            if (!large_text.empty()) {
                out["large_text"] = large_text;
            }
            if (!small_text.empty()) {
                out["small_text"] = small_text;
            }
            return out;
		}
	};

    // https://discord.com/developers/docs/topics/gateway#activity-object-activity-party
    struct ActivityParty: public apiStruct {
        snowflake id = 0; // Optional
        int current_size = 0, max_size = 0; // Optional

        bool isValid() const{
            return id != 0 ||
                    (current_size != 0 && max_size != 0);
        }
		json toJson() const{
            json out;
            if (id != 0) {
                out["id"] = id;
            }
            if (current_size != 0 && max_size != 0) {
                out["size"] = json({current_size, max_size});
            }
            return out;
		}
	};

    // https://discord.com/developers/docs/topics/gateway#activity-object-activity-emoji
    struct ActivityEmoji{
        std::string name;
        snowflake id = 0; // Optional
        bool animated = false; // Optional

        bool isValid() const{
            return !name.empty();
        }
		json toJson() const{
            json out;
            out["name"] = name;
            out["animated"] = animated;
            if (id != 0){
                out["id"] = id;
            }
            return out;
		}
	};

    // https://discord.com/developers/docs/topics/gateway#activity-object-activity-timestamps
    struct ActivityTimestamps: public apiStruct {
        int start = 0; // Optional
        int end = 0; // Optional

        bool isValid() const{
            return start != 0 || end != 0;
        }
        json toJson() const{
            json out;
            if (start != 0){
                out["start"] = start;
            }
            if (end != 0){
                out["end"] = end;
            }
            return out;
		}
	};

    // https://discord.com/developers/docs/topics/gateway#activity-object
    struct Activity: public apiStruct {
        bool isValid() const{
            return true;
        }

        std::string name;
		enum type{
			Game, Streaming, Listening, Custom
		}type = Game;
		std::string url;
        int created_at = 0;
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

		json toJson() const{
			json out{
					{"name", name},
					{"type", type}
			};
            if(!url.empty()){
				out["url"] = url;
			}
            if(created_at != 0){
                out["created_at"] = created_at;
			}
            if(timestamps.isValid()){
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
            if(emoji.isValid()){
				out["emoji"] = emoji.toJson();
			}
            if(party.isValid()){
				out["party"] = party.toJson();
			}
            if(assets.isValid()){
				out["assets"] = assets.toJson();
			}
            if(secrets.isValid()){
				out["secrets"] = secrets.toJson();
			}
			if(instance != undefined){
				out["instance"] = (bool)instance;
			}
            if(flags.isValid()){
				out["flags"] = flags.toJson();
            }
            std::clog << out << std::endl;
			return out;
		}
	};

    // https://discord.com/developers/docs/topics/gateway#update-status
	struct Status{
        time_t since = 0;
		Activity game;
		enum status{
			online, dnd, idle, invisible, offline
		}status = online;
		bool afk = false;

		json toJson() const{
			json out;
            out["since"] = since;
            if(game.isValid()){
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
                const json &channel,
                const std::string &message,
                const std::function<void(const json)> &callback = [](const json &){}
        ){
            sendMessage(channel.get<std::string>(), message, callback);
        }

		virtual void sendMessage(
				const snowflake &channel,
				const std::string &message,
				const std::function<void(const json)> &callback = [](const json &){}
		){
			std::ostringstream message_str;
			message_str << "/channels/" << channel << "/messages";
			sendMessage(channel, message_str.str(), callback);
		}

		virtual void sendMessage(
				const std::string &channel,
				const std::string &message,
				const std::function<void(const json)> &callback = [](const json &){}
		){
			std::ostringstream target;
			target << "/channels/" << channel << "/messages";
			call(
                    std::make_shared<std::string>("POST"),
                    std::make_shared<std::string>(target.str()),
                    std::make_shared<json>(json({{"content", message}})),
                    std::make_shared<std::function<void(const json)>>(callback)
			);
		}

		virtual void setStatus(
				const Status &status,
				const std::function<void()> &callback = [](){}
		){
			send(
					3,
					std::make_shared<json>(status.toJson()),
					std::make_shared<std::function<void()>>(callback)
			);
		}
	};
}
