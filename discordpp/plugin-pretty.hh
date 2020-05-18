#pragma once

namespace discordpp{
	// Presence Update
	struct Activity{
		bool active = true;
		json toJson(){
			return json();
		}
	};
	// Presence Update
	struct Status{
		int since = -1;
		Activity game;
		enum status {online, dnd, idle, invisible, offline}status = online;
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

	};
}