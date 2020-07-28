#pragma once

namespace discordpp{
    struct apiStruct {
        virtual bool isValid() const = 0;
        virtual json toJson() const = 0;
    };


    // Begin embed structs
    // https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure
    struct EmbedFooter: public apiStruct {
        std::string text;
        std::string icon_url; // Optional
        std::string proxy_icon_url; // Optional

        bool isValid() const{
            return !text.empty();
        }
        json toJson() const{
            json out;
            out["text"] = text;
            if (!icon_url.empty()) {
                out["icon_url"] = icon_url;
            }
            if (!proxy_icon_url.empty()) {
                out["proxy_icon_url"] = proxy_icon_url;
            }
            return out;
        }
    };

    // https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure
    struct EmbedImage: public apiStruct {
        // All optional:
        std::string url;
        std::string proxy_url;
        int height = 0;
        int width = 0;

        bool isValid() const{
            return !url.empty() || !proxy_url.empty();
        }
        json toJson() const{
            json out;
            if (!url.empty()) {
                out["url"] = url;
            }
            if (!proxy_url.empty()) {
                out["proxy_url"] = proxy_url;
            }
            if (height > 0 && width > 0) {
                out["height"] = height;
                out["width"] = width;
            }
            return out;
        }
    };

    // https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure
    typedef EmbedImage EmbedThumbnail;

    // https://discord.com/developers/docs/resources/channel#embed-object-embed-video-structure
    typedef EmbedImage EmbedVideo;

    // https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure
    struct EmbedProvider: public apiStruct {
        std::string name; // Otpional
        std::string url; // Optional

        bool isValid() const{
            return !name.empty() || !url.empty();
        }
        json toJson() const{
            json out;
            if (!name.empty()) {
                out["name"] = name;
            }
            if (!url.empty()) {
                out["url"] = url;
            }
            return out;
        }
    };

    // https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure
    struct EmbedAuthor: public apiStruct {
        // All optional:
        std::string name;
        std::string url;
        std::string icon_url;
        std::string proxy_icon_url;

        bool isValid() const{
            return !name.empty() || !url.empty() ||
                    !icon_url.empty() || !proxy_icon_url.empty();
        }
        json toJson() const{
            json out;
            if (!name.empty()) {
                out["name"] = name;
            }
            if (!url.empty()) {
                out["url"] = url;
            }
            if (!icon_url.empty()) {
                out["icon_url"] = url;
            }
            if (!proxy_icon_url.empty()) {
                out["proxy_icon_url"] = url;
            }
            return out;
        }
    };

    // https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure
    struct EmbedField: public apiStruct {
        std::string name;
        std::string value;
        bool in_line = true; // Optional

        bool isValid() const{
            return !name.empty() && !value.empty();
        }
        json toJson() const{
            json out;
            out["name"] = name;
            out["value"] = value;
            out["inline"] = in_line;
            return out;
        }
    };

    // https://discord.com/developers/docs/resources/channel#embed-object
    struct Embed: public apiStruct {
        // All optional:
        std::string title;
        enum type{
            rich, img, vid, gifv, article, link
        }type=rich;
        std::string description;
        std::string url;
        std::string timestamp;
        int color = 0;
        EmbedFooter footer;
        EmbedImage image;
        EmbedThumbnail thumbnail;
        EmbedVideo video;
        EmbedProvider provider;
        EmbedAuthor author;
        std::vector<EmbedField> fields;

        bool isValid() const{
            return true;
        }
        json toJson() const{
            json out;
            out["color"] = color;
            switch(type){
                    case rich:
                            out["type"] = "rich";
                            break;
                    case img:
                            out["type"] = "image";
                            break;
                    case vid:
                            out["type"] = "video";
                            break;
                    case gifv:
                            out["type"] = "gifv";
                            break;
                    case link:
                            out["type"] = "link";
                            break;
            }
            if (!description.empty()) {
                out["description"] = description;
            }
            if (!url.empty()) {
                out["url"] = url;
            }
            if (!timestamp.empty()) {
                out["timestamp"] = timestamp;
            }
            if (image.isValid()) {
                out["image"] = image.toJson();
            }
            if (thumbnail.isValid()) {
                out["thumbnail"] = thumbnail.toJson();
            }
            if (video.isValid()) {
                out["video"] = video.toJson();
            }
            if (provider.isValid()) {
                out["provider"] = provider.toJson();
            }
            if (author.isValid()) {
                out["author"] = author.toJson();
            }
            std::vector<json> embfields;
            for (auto it = fields.begin(); it != fields.end(); it++) {
                embfields.push_back((*it).toJson());
            }
            out["fields"] = json(embfields);
            return out;
        }
    };
    // End embed structs

    // Begin status structs
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

        std::string name = "undefined";
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
        // End status structs

    template<class BASE>
    class PluginPretty: public BASE, virtual BotStruct{
    public:
        // Without embeds
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

        // With embeds
        virtual void sendMessage(
                const json &channel,
                const std::string &message,
                const Embed &embed,
                const std::function<void(const json)> &callback = [](const json &){}
        ){
            sendMessage(channel.get<std::string>(), message, embed, callback);
        }
        virtual void sendMessage(
                const snowflake &channel,
                const std::string &message,
                const Embed &embed,
                const std::function<void(const json)> &callback = [](const json &){}
        ){
            std::ostringstream message_str;
            message_str << "/channels/" << channel << "/messages";
            sendMessage(channel, message_str.str(), embed, callback);
        }
        virtual void sendMessage(
                const std::string &channel,
                const std::string &message,
                const Embed &embed,
                const std::function<void(const json)> &callback = [](const json &){}
        ){
            std::ostringstream target;
            target << "/channels/" << channel << "/messages";
            json out = {{"embed", embed.toJson()}};
            if (!message.empty()) {
                out["content"] = message;
            }
            call(
                    std::make_shared<std::string>("POST"),
                    std::make_shared<std::string>(target.str()),
                    std::make_shared<json>(out),
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
