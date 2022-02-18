#ifndef ENGINE_EXT_LDTK_HPP
#define ENGINE_EXT_LDTK_HPP

#include "json.hpp"

#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER
namespace nlohmann {
template <typename T>
struct adl_serializer<std::shared_ptr<T>> {
    static void to_json(json & j, const std::shared_ptr<T> & opt) {
        if (!opt) j = nullptr; else j = *opt;
    }

    static std::shared_ptr<T> from_json(const json & j) {
        if (j.is_null()) return std::unique_ptr<T>(); else return std::unique_ptr<T>(new T(j.get<T>()));
    }
};
}
#endif

namespace quicktype {
using nlohmann::json;

inline json get_untyped(const json & j, const char * property) {
    if (j.find(property) != j.end()) {
        return j.at(property).get<json>();
    }
    return json();
}

inline json get_untyped(const json & j, std::string property) {
    return get_untyped(j, property.data());
}

template <typename T>
inline std::shared_ptr<T> get_optional(const json & j, const char * property) {
    if (j.find(property) != j.end()) {
        return j.at(property).get<std::shared_ptr<T>>();
    }
    return std::shared_ptr<T>();
}

template <typename T>
inline std::shared_ptr<T> get_optional(const json & j, std::string property) {
    return get_optional<T>(j, property.data());
}

/**
 * Possible values: `Hidden`, `ValueOnly`, `NameAndValue`, `EntityTile`, `Points`,
 * `PointStar`, `PointPath`, `PointPathLoop`, `RadiusPx`, `RadiusGrid`
 */
enum class editor_display_mode : int { entity_tile, hidden, name_and_value, point_path, point_path_loop, point_star, points, radius_grid, radius_px, value_only };

/**
 * Possible values: `Above`, `Center`, `Beneath`
 */
enum class editor_display_pos : int { above, beneath, center };

enum class text_language_mode : int { lang_c, lang_haxe, lang_js, lang_json, lang_lua, lang_markdown, lang_python, lang_ruby, lang_xml };

/**
 * This section is mostly only intended for the LDtk editor app itself. You can safely
 * ignore it.
 */
struct field_definition {
    /**
     * Human readable value type (eg. `Int`, `Float`, `Point`, etc.). If the field is an array,
     * this field will look like `Array<...>` (eg. `Array<Int>`, `Array<Point>` etc.)
     */
    std::string type;
    /**
     * Optional list of accepted file extensions for FilePath value type. Includes the dot:
     * `.ext`
     */
    std::shared_ptr<std::vector<std::string>> accept_file_types;
    /**
     * Array max length
     */
    std::shared_ptr<int64_t> array_max_length;
    /**
     * Array min length
     */
    std::shared_ptr<int64_t> array_min_length;
    /**
     * TRUE if the value can be null. For arrays, TRUE means it can contain null values
     * (exception: array of Points can't have null values).
     */
    bool can_be_null;
    /**
     * Default value if selected value is null or invalid.
     */
    nlohmann::json default_override;
    bool editor_always_show;
    bool editor_cut_long_values;
    /**
     * Possible values: `Hidden`, `ValueOnly`, `NameAndValue`, `EntityTile`, `Points`,
     * `PointStar`, `PointPath`, `PointPathLoop`, `RadiusPx`, `RadiusGrid`
     */
    editor_display_mode editor_display_mode;
    /**
     * Possible values: `Above`, `Center`, `Beneath`
     */
    editor_display_pos editor_display_pos;
    /**
     * Unique String identifier
     */
    std::string identifier;
    /**
     * TRUE if the value is an array of multiple values
     */
    bool is_array;
    /**
     * Max limit for value, if applicable
     */
    std::shared_ptr<double> max;
    /**
     * Min limit for value, if applicable
     */
    std::shared_ptr<double> min;
    /**
     * Optional regular expression that needs to be matched to accept values. Expected format:
     * `/some_reg_ex/g`, with optional "i" flag.
     */
    std::shared_ptr<std::string> regex;
    /**
     * Possible values: &lt;`null`&gt;, `LangPython`, `LangRuby`, `LangJS`, `LangLua`, `LangC`,
     * `LangHaxe`, `LangMarkdown`, `LangJson`, `LangXml`
     */
    std::shared_ptr<text_language_mode> text_language_mode;
    /**
     * Internal type enum
     */
    nlohmann::json field_definition_type;
    /**
     * Unique Int identifier
     */
    int64_t uid;
};

/**
 * Possible values: `DiscardOldOnes`, `PreventAdding`, `MoveLastOne`
 */
enum class limit_behavior : int { discard_old_ones, move_last_one, prevent_adding };

/**
 * If TRUE, the maxCount is a "per world" limit, if FALSE, it's a "per level". Possible
 * values: `PerLayer`, `PerLevel`, `PerWorld`
 */
enum class limit_scope : int { per_layer, per_level, per_world };

/**
 * Possible values: `Rectangle`, `Ellipse`, `Tile`, `Cross`
 */
enum class render_mode : int { cross, ellipse, rectangle, tile };

/**
 * Possible values: `Cover`, `FitInside`, `Repeat`, `Stretch`
 */
enum class tile_render_mode : int { cover, fit_inside, repeat, stretch };

struct entity_definition {
    /**
     * Base entity color
     */
    std::string color;
    /**
     * Array of field definitions
     */
    std::vector<field_definition> field_defs;
    double fill_opacity;
    /**
     * Pixel height
     */
    int64_t height;
    bool hollow;
    /**
     * Unique String identifier
     */
    std::string identifier;
    /**
     * Only applies to entities resizable on both X/Y. If TRUE, the entity instance width/height
     * will keep the same aspect ratio as the definition.
     */
    bool keep_aspect_ratio;
    /**
     * Possible values: `DiscardOldOnes`, `PreventAdding`, `MoveLastOne`
     */
    limit_behavior limit_behavior;
    /**
     * If TRUE, the maxCount is a "per world" limit, if FALSE, it's a "per level". Possible
     * values: `PerLayer`, `PerLevel`, `PerWorld`
     */
    limit_scope limit_scope;
    double line_opacity;
    /**
     * Max instances count
     */
    int64_t max_count;
    /**
     * Pivot X coordinate (from 0 to 1.0)
     */
    double pivot_x;
    /**
     * Pivot Y coordinate (from 0 to 1.0)
     */
    double pivot_y;
    /**
     * Possible values: `Rectangle`, `Ellipse`, `Tile`, `Cross`
     */
    render_mode render_mode;
    /**
     * If TRUE, the entity instances will be resizable horizontally
     */
    bool resizable_x;
    /**
     * If TRUE, the entity instances will be resizable vertically
     */
    bool resizable_y;
    /**
     * Display entity name in editor
     */
    bool show_name;
    /**
     * An array of strings that classifies this entity
     */
    std::vector<std::string> tags;
    /**
     * Tile ID used for optional tile display
     */
    std::shared_ptr<int64_t> tile_id;
    /**
     * Possible values: `Cover`, `FitInside`, `Repeat`, `Stretch`
     */
    tile_render_mode tile_render_mode;
    /**
     * Tileset ID used for optional tile display
     */
    std::shared_ptr<int64_t> tileset_id;
    /**
     * Unique Int identifier
     */
    int64_t uid;
    /**
     * Pixel width
     */
    int64_t width;
};

struct enum_value_definition {
    /**
     * An array of 4 Int values that refers to the tile in the tileset image: `[ x, y, width,
     * height ]`
     */
    std::shared_ptr<std::vector<int64_t>> tile_src_rect;
    /**
     * Optional color
     */
    int64_t color;
    /**
     * Enum value
     */
    std::string id;
    /**
     * The optional ID of the tile
     */
    std::shared_ptr<int64_t> tile_id;
};

struct enum_definition {
    std::shared_ptr<std::string> external_file_checksum;
    /**
     * Relative path to the external file providing this Enum
     */
    std::shared_ptr<std::string> external_rel_path;
    /**
     * Tileset UID if provided
     */
    std::shared_ptr<int64_t> icon_tileset_uid;
    /**
     * Unique String identifier
     */
    std::string identifier;
    /**
     * Unique Int identifier
     */
    int64_t uid;
    /**
     * All possible enum values, with their optional Tile infos.
     */
    std::vector<enum_value_definition> values;
};

/**
 * Checker mode Possible values: `None`, `Horizontal`, `Vertical`
 */
enum class checker : int { horizontal, none, vertical };

/**
 * Defines how tileIds array is used Possible values: `Single`, `Stamp`
 */
enum class tile_mode : int { single, stamp };

/**
 * This complex section isn't meant to be used by game devs at all, as these rules are
 * completely resolved internally by the editor before any saving. You should just ignore
 * this part.
 */
struct auto_layer_rule_definition {
    /**
     * If FALSE, the rule effect isn't applied, and no tiles are generated.
     */
    bool active;
    /**
     * When TRUE, the rule will prevent other rules to be applied in the same cell if it matches
     * (TRUE by default).
     */
    bool break_on_match;
    /**
     * Chances for this rule to be applied (0 to 1)
     */
    double chance;
    /**
     * Checker mode Possible values: `None`, `Horizontal`, `Vertical`
     */
    checker checker;
    /**
     * If TRUE, allow rule to be matched by flipping its pattern horizontally
     */
    bool flip_x;
    /**
     * If TRUE, allow rule to be matched by flipping its pattern vertically
     */
    bool flip_y;
    /**
     * Default IntGrid value when checking cells outside of level bounds
     */
    std::shared_ptr<int64_t> out_of_bounds_value;
    /**
     * Rule pattern (size x size)
     */
    std::vector<int64_t> pattern;
    /**
     * If TRUE, enable Perlin filtering to only apply rule on specific random area
     */
    bool perlin_active;
    double perlin_octaves;
    double perlin_scale;
    double perlin_seed;
    /**
     * X pivot of a tile stamp (0-1)
     */
    double pivot_x;
    /**
     * Y pivot of a tile stamp (0-1)
     */
    double pivot_y;
    /**
     * Pattern width & height. Should only be 1,3,5 or 7.
     */
    int64_t size;
    /**
     * Array of all the tile IDs. They are used randomly or as stamps, based on `tileMode` value.
     */
    std::vector<int64_t> tile_ids;
    /**
     * Defines how tileIds array is used Possible values: `Single`, `Stamp`
     */
    tile_mode tile_mode;
    /**
     * Unique Int identifier
     */
    int64_t uid;
    /**
     * X cell coord modulo
     */
    int64_t x_modulo;
    /**
     * Y cell coord modulo
     */
    int64_t y_modulo;
};

struct auto_layer_rule_group {
    bool active;
    bool collapsed;
    bool is_optional;
    std::string name;
    std::vector<auto_layer_rule_definition> rules;
    int64_t uid;
};

/**
 * IntGrid value definition
 */
struct int_grid_value_definition {
    std::string color;
    /**
     * Unique String identifier
     */
    std::shared_ptr<std::string> identifier;
    /**
     * The IntGrid value itself
     */
    int64_t value;
};

/**
 * Type of the layer as Haxe Enum Possible values: `IntGrid`, `Entities`, `Tiles`,
 * `AutoLayer`
 */
enum class type : int { auto_layer, entities, int_grid, tiles };

struct layer_definition {
    /**
     * Type of the layer (*IntGrid, Entities, Tiles or AutoLayer*)
     */
    std::string type;
    /**
     * Contains all the auto-layer rule definitions.
     */
    std::vector<auto_layer_rule_group> auto_rule_groups;
    std::shared_ptr<int64_t> auto_source_layer_def_uid;
    /**
     * Reference to the Tileset UID being used by this auto-layer rules. WARNING: some layer
     * *instances* might use a different tileset. So most of the time, you should probably use
     * the `__tilesetDefUid` value from layer instances.
     */
    std::shared_ptr<int64_t> auto_tileset_def_uid;
    /**
     * Opacity of the layer (0 to 1.0)
     */
    double display_opacity;
    /**
     * An array of tags to forbid some Entities in this layer
     */
    std::vector<std::string> excluded_tags;
    /**
     * Width and height of the grid in pixels
     */
    int64_t grid_size;
    /**
     * Unique String identifier
     */
    std::string identifier;
    /**
     * An array that defines extra optional info for each IntGrid value. The array is sorted
     * using value (ascending).
     */
    std::vector<int_grid_value_definition> int_grid_values;
    /**
     * X offset of the layer, in pixels (IMPORTANT: this should be added to the `LayerInstance`
     * optional offset)
     */
    int64_t px_offset_x;
    /**
     * Y offset of the layer, in pixels (IMPORTANT: this should be added to the `LayerInstance`
     * optional offset)
     */
    int64_t px_offset_y;
    /**
     * An array of tags to filter Entities that can be added to this layer
     */
    std::vector<std::string> required_tags;
    /**
     * If the tiles are smaller or larger than the layer grid, the pivot value will be used to
     * position the tile relatively its grid cell.
     */
    double tile_pivot_x;
    /**
     * If the tiles are smaller or larger than the layer grid, the pivot value will be used to
     * position the tile relatively its grid cell.
     */
    double tile_pivot_y;
    /**
     * Reference to the Tileset UID being used by this Tile layer. WARNING: some layer
     * *instances* might use a different tileset. So most of the time, you should probably use
     * the `__tilesetDefUid` value from layer instances.
     */
    std::shared_ptr<int64_t> tileset_def_uid;
    /**
     * Type of the layer as Haxe Enum Possible values: `IntGrid`, `Entities`, `Tiles`,
     * `AutoLayer`
     */
    type layer_definition_type;
    /**
     * Unique Int identifier
     */
    int64_t uid;
};

/**
 * The `Tileset` definition is the most important part among project definitions. It
 * contains some extra informations about each integrated tileset. If you only had to parse
 * one definition section, that would be the one.
 */
struct tileset_definition {
    /**
     * Grid-based height
     */
    int64_t c_hei;
    /**
     * Grid-based width
     */
    int64_t c_wid;
    /**
     * The following data is used internally for various optimizations. It's always synced with
     * source image changes.
     */
    std::shared_ptr<std::map<std::string, nlohmann::json>> cached_pixel_data;
    /**
     * An array of custom tile metadata
     */
    std::vector<std::map<std::string, nlohmann::json>> custom_data;
    /**
     * Tileset tags using Enum values specified by `tagsSourceEnumId`. This array contains 1
     * element per Enum value, which contains an array of all Tile IDs that are tagged with it.
     */
    std::vector<std::map<std::string, nlohmann::json>> enum_tags;
    /**
     * Unique String identifier
     */
    std::string identifier;
    /**
     * Distance in pixels from image borders
     */
    int64_t padding;
    /**
     * Image height in pixels
     */
    int64_t px_hei;
    /**
     * Image width in pixels
     */
    int64_t px_wid;
    /**
     * Path to the source file, relative to the current project JSON file
     */
    std::string rel_path;
    /**
     * Array of group of tiles selections, only meant to be used in the editor
     */
    std::vector<std::map<std::string, nlohmann::json>> saved_selections;
    /**
     * Space in pixels between all tiles
     */
    int64_t spacing;
    /**
     * Optional Enum definition UID used for this tileset meta-data
     */
    std::shared_ptr<int64_t> tags_source_enum_uid;
    int64_t tile_grid_size;
    /**
     * Unique Intidentifier
     */
    int64_t uid;
};

/**
 * A structure containing all the definitions of this project
 *
 * If you're writing your own LDtk importer, you should probably just ignore *most* stuff in
 * the `defs` section, as it contains data that are mostly important to the editor. To keep
 * you away from the `defs` section and avoid some unnecessary JSON parsing, important data
 * from definitions is often duplicated in fields prefixed with a double underscore (eg.
 * `__identifier` or `__type`).  The 2 only definition types you might need here are
 * **Tilesets** and **Enums**.
 */
struct definitions {
    /**
     * All entities definitions, including their custom fields
     */
    std::vector<entity_definition> entities;
    /**
     * All internal enums
     */
    std::vector<enum_definition> enums;
    /**
     * Note: external enums are exactly the same as `enums`, except they have a `relPath` to
     * point to an external source file.
     */
    std::vector<enum_definition> external_enums;
    /**
     * All layer definitions
     */
    std::vector<layer_definition> layers;
    /**
     * All custom fields available to all levels.
     */
    std::vector<field_definition> level_fields;
    /**
     * All tilesets
     */
    std::vector<tileset_definition> tilesets;
};

enum class flag : int { discard_pre_csv_int_grid, ignore_backup_suggest };

/**
 * "Image export" option when saving project. Possible values: `None`, `OneImagePerLayer`,
 * `OneImagePerLevel`
 */
enum class image_export_mode : int { none, one_image_per_layer, one_image_per_level };

/**
 * Level background image position info
 */
struct level_background_position {
    /**
     * An array of 4 float values describing the cropped sub-rectangle of the displayed
     * background image. This cropping happens when original is larger than the level bounds.
     * Array format: `[ cropX, cropY, cropWidth, cropHeight ]`
     */
    std::vector<double> crop_rect;
    /**
     * An array containing the `[scaleX,scaleY]` values of the **cropped** background image,
     * depending on `bgPos` option.
     */
    std::vector<double> scale;
    /**
     * An array containing the `[x,y]` pixel coordinates of the top-left corner of the
     * **cropped** background image, depending on `bgPos` option.
     */
    std::vector<int64_t> top_left_px;
};

struct field_instance {
    /**
     * Field definition identifier
     */
    std::string identifier;
    /**
     * Type of the field, such as `Int`, `Float`, `Enum(my_enum_name)`, `Bool`, etc.
     */
    std::string type;
    /**
     * Actual value of the field instance. The value type may vary, depending on `__type`
     * (Integer, Boolean, String etc.)<br/>  It can also be an `Array` of those same types.
     */
    nlohmann::json value;
    /**
     * Reference of the **Field definition** UID
     */
    int64_t def_uid;
    /**
     * Editor internal raw values
     */
    std::vector<nlohmann::json> real_editor_values;
};

/**
 * This structure represents a single tile from a given Tileset.
 */
struct tile_instance {
    /**
     * Internal data used by the editor.<br/>  For auto-layer tiles: `[ruleId, coordId]`.<br/>
     * For tile-layer tiles: `[coordId]`.
     */
    std::vector<int64_t> d;
    /**
     * "Flip bits", a 2-bits integer to represent the mirror transformations of the tile.<br/>
     * - Bit 0 = X flip<br/>   - Bit 1 = Y flip<br/>   Examples: f=0 (no flip), f=1 (X flip
     * only), f=2 (Y flip only), f=3 (both flips)
     */
    int64_t f;
    /**
     * Pixel coordinates of the tile in the **layer** (`[x,y]` format). Don't forget optional
     * layer offsets, if they exist!
     */
    std::vector<int64_t> px;
    /**
     * Pixel coordinates of the tile in the **tileset** (`[x,y]` format)
     */
    std::vector<int64_t> src;
    /**
     * The *Tile ID* in the corresponding tileset.
     */
    int64_t t;
};

/**
 * Tile data in an Entity instance
 */
struct entity_instance_tile {
    /**
     * An array of 4 Int values that refers to the tile in the tileset image: `[ x, y, width,
     * height ]`
     */
    std::vector<int64_t> src_rect;
    /**
     * Tileset ID
     */
    int64_t tileset_uid;
};

struct entity_instance {
    /**
     * Grid-based coordinates (`[x,y]` format)
     */
    std::vector<int64_t> grid;
    /**
     * Entity definition identifier
     */
    std::string identifier;
    /**
     * Pivot coordinates  (`[x,y]` format, values are from 0 to 1) of the Entity
     */
    std::vector<double> pivot;
    /**
     * Optional Tile used to display this entity (it could either be the default Entity tile, or
     * some tile provided by a field value, like an Enum).
     */
    std::shared_ptr<entity_instance_tile> tile;
    /**
     * Reference of the **Entity definition** UID
     */
    int64_t def_uid;
    /**
     * An array of all custom fields and their values.
     */
    std::vector<field_instance> field_instances;
    /**
     * Entity height in pixels. For non-resizable entities, it will be the same as Entity
     * definition.
     */
    int64_t height;
    /**
     * Pixel coordinates (`[x,y]` format) in current level coordinate space. Don't forget
     * optional layer offsets, if they exist!
     */
    std::vector<int64_t> px;
    /**
     * Entity width in pixels. For non-resizable entities, it will be the same as Entity
     * definition.
     */
    int64_t width;
};

/**
 * IntGrid value instance
 */
struct int_grid_value_instance {
    /**
     * Coordinate ID in the layer grid
     */
    int64_t coord_id;
    /**
     * IntGrid value
     */
    int64_t v;
};

struct layer_instance {
    /**
     * Grid-based height
     */
    int64_t c_hei;
    /**
     * Grid-based width
     */
    int64_t c_wid;
    /**
     * Grid size
     */
    int64_t grid_size;
    /**
     * Layer definition identifier
     */
    std::string identifier;
    /**
     * Layer opacity as Float [0-1]
     */
    double opacity;
    /**
     * Total layer X pixel offset, including both instance and definition offsets.
     */
    int64_t px_total_offset_x;
    /**
     * Total layer Y pixel offset, including both instance and definition offsets.
     */
    int64_t px_total_offset_y;
    /**
     * The definition UID of corresponding Tileset, if any.
     */
    std::shared_ptr<int64_t> tileset_def_uid;
    /**
     * The relative path to corresponding Tileset, if any.
     */
    std::shared_ptr<std::string> tileset_rel_path;
    /**
     * Layer type (possible values: IntGrid, Entities, Tiles or AutoLayer)
     */
    std::string type;
    /**
     * An array containing all tiles generated by Auto-layer rules. The array is already sorted
     * in display order (ie. 1st tile is beneath 2nd, which is beneath 3rd etc.).<br/><br/>
     * Note: if multiple tiles are stacked in the same cell as the result of different rules,
     * all tiles behind opaque ones will be discarded.
     */
    std::vector<tile_instance> auto_layer_tiles;
    std::vector<entity_instance> entity_instances;
    std::vector<tile_instance> grid_tiles;
    /**
     * **WARNING**: this deprecated value will be *removed* completely on version 0.10.0+
     * Replaced by: `intGridCsv`
     */
    std::shared_ptr<std::vector<int_grid_value_instance>> int_grid;
    /**
     * A list of all values in the IntGrid layer, stored from left to right, and top to bottom
     * (ie. first row from left to right, followed by second row, etc). `0` means "empty cell"
     * and IntGrid values start at 1. This array size is `__cWid` x `__cHei` cells.
     */
    std::vector<int64_t> int_grid_csv;
    /**
     * Reference the Layer definition UID
     */
    int64_t layer_def_uid;
    /**
     * Reference to the UID of the level containing this layer instance
     */
    int64_t level_id;
    /**
     * An Array containing the UIDs of optional rules that were enabled in this specific layer
     * instance.
     */
    std::vector<int64_t> optional_rules;
    /**
     * This layer can use another tileset by overriding the tileset UID here.
     */
    std::shared_ptr<int64_t> override_tileset_uid;
    /**
     * X offset in pixels to render this layer, usually 0 (IMPORTANT: this should be added to
     * the `LayerDef` optional offset, see `__pxTotalOffsetX`)
     */
    int64_t px_offset_x;
    /**
     * Y offset in pixels to render this layer, usually 0 (IMPORTANT: this should be added to
     * the `LayerDef` optional offset, see `__pxTotalOffsetY`)
     */
    int64_t px_offset_y;
    /**
     * Random seed used for Auto-Layers rendering
     */
    int64_t seed;
    /**
     * Layer instance visibility
     */
    bool visible;
};

enum class bg_pos : int { contain, cover, cover_dirty, unscaled };

/**
 * Nearby level info
 */
struct neighbour_level {
    /**
     * A single lowercase character tipping on the level location (`n`orth, `s`outh, `w`est,
     * `e`ast).
     */
    std::string dir;
    int64_t level_uid;
};

/**
 * This section contains all the level data. It can be found in 2 distinct forms, depending
 * on Project current settings:  - If "*Separate level files*" is **disabled** (default):
 * full level data is *embedded* inside the main Project JSON file, - If "*Separate level
 * files*" is **enabled**: level data is stored in *separate* standalone `.ldtkl` files (one
 * per level). In this case, the main Project JSON file will still contain most level data,
 * except heavy sections, like the `layerInstances` array (which will be null). The
 * `externalRelPath` string points to the `ldtkl` file.  A `ldtkl` file is just a JSON file
 * containing exactly what is described below.
 */
struct level {
    /**
     * Background color of the level (same as `bgColor`, except the default value is
     * automatically used here if its value is `null`)
     */
    std::string bg_color;
    /**
     * Position informations of the background image, if there is one.
     */
    std::shared_ptr<level_background_position> bg_pos;
    /**
     * An array listing all other levels touching this one on the world map. In "linear" world
     * layouts, this array is populated with previous/next levels in array, and `dir` depends on
     * the linear horizontal/vertical layout.
     */
    std::vector<neighbour_level> neighbours;
    /**
     * Background color of the level. If `null`, the project `defaultLevelBgColor` should be
     * used.
     */
    std::shared_ptr<std::string> level_bg_color;
    /**
     * Background image X pivot (0-1)
     */
    double bg_pivot_x;
    /**
     * Background image Y pivot (0-1)
     */
    double bg_pivot_y;
    /**
     * An enum defining the way the background image (if any) is positioned on the level. See
     * `__bgPos` for resulting position info. Possible values: &lt;`null`&gt;, `Unscaled`,
     * `Contain`, `Cover`, `CoverDirty`
     */
    std::shared_ptr<bg_pos> level_bg_pos;
    /**
     * The *optional* relative path to the level background image.
     */
    std::shared_ptr<std::string> bg_rel_path;
    /**
     * This value is not null if the project option "*Save levels separately*" is enabled. In
     * this case, this **relative** path points to the level Json file.
     */
    std::shared_ptr<std::string> external_rel_path;
    /**
     * An array containing this level custom field values.
     */
    std::vector<field_instance> field_instances;
    /**
     * Unique String identifier
     */
    std::string identifier;
    /**
     * An array containing all Layer instances. **IMPORTANT**: if the project option "*Save
     * levels separately*" is enabled, this field will be `null`.<br/>  This array is **sorted
     * in display order**: the 1st layer is the top-most and the last is behind.
     */
    std::shared_ptr<std::vector<layer_instance>> layer_instances;
    /**
     * Height of the level in pixels
     */
    int64_t px_hei;
    /**
     * Width of the level in pixels
     */
    int64_t px_wid;
    /**
     * Unique Int identifier
     */
    int64_t uid;
    /**
     * If TRUE, the level identifier will always automatically use the naming pattern as defined
     * in `Project.levelNamePattern`. Becomes FALSE if the identifier is manually modified by
     * user.
     */
    bool use_auto_identifier;
    /**
     * World X coordinate in pixels
     */
    int64_t world_x;
    /**
     * World Y coordinate in pixels
     */
    int64_t world_y;
};

/**
 * An enum that describes how levels are organized in this project (ie. linearly or in a 2D
 * space). Possible values: `Free`, `GridVania`, `LinearHorizontal`, `LinearVertical`
 */
enum class world_layout : int { free, grid_vania, linear_horizontal, linear_vertical };

/**
 * This file is a JSON schema of files created by LDtk level editor (https://ldtk.io).
 *
 * This is the root of any Project JSON file. It contains:  - the project settings, - an
 * array of levels, - a group of definitions (that can probably be safely ignored for most
 * users).
 */
struct ldtk {
    /**
     * Number of backup files to keep, if the `backupOnSave` is TRUE
     */
    int64_t backup_limit;
    /**
     * If TRUE, an extra copy of the project will be created in a sub folder, when saving.
     */
    bool backup_on_save;
    /**
     * Project background color
     */
    std::string bg_color;
    /**
     * Default grid size for new layers
     */
    int64_t default_grid_size;
    /**
     * Default background color of levels
     */
    std::string default_level_bg_color;
    /**
     * Default new level height
     */
    int64_t default_level_height;
    /**
     * Default new level width
     */
    int64_t default_level_width;
    /**
     * Default X pivot (0 to 1) for new entities
     */
    double default_pivot_x;
    /**
     * Default Y pivot (0 to 1) for new entities
     */
    double default_pivot_y;
    /**
     * A structure containing all the definitions of this project
     */
    definitions defs;
    /**
     * **WARNING**: this deprecated value is no longer exported since version 0.9.3  Replaced
     * by: `imageExportMode`
     */
    std::shared_ptr<bool> export_png;
    /**
     * If TRUE, a Tiled compatible file will also be generated along with the LDtk JSON file
     * (default is FALSE)
     */
    bool export_tiled;
    /**
     * If TRUE, one file will be saved for the project (incl. all its definitions) and one file
     * in a sub-folder for each level.
     */
    bool external_levels;
    /**
     * An array containing various advanced flags (ie. options or other states). Possible
     * values: `DiscardPreCsvIntGrid`, `IgnoreBackupSuggest`
     */
    std::vector<flag> flags;
    /**
     * "Image export" option when saving project. Possible values: `None`, `OneImagePerLayer`,
     * `OneImagePerLevel`
     */
    image_export_mode image_export_mode;
    /**
     * File format version
     */
    std::string json_version;
    /**
     * The default naming convention for level identifiers.
     */
    std::string level_name_pattern;
    /**
     * All levels. The order of this array is only relevant in `LinearHorizontal` and
     * `linearVertical` world layouts (see `worldLayout` value). Otherwise, you should refer to
     * the `worldX`,`worldY` coordinates of each Level.
     */
    std::vector<level> levels;
    /**
     * If TRUE, the Json is partially minified (no indentation, nor line breaks, default is
     * FALSE)
     */
    bool minify_json;
    /**
     * Next Unique integer ID available
     */
    int64_t next_uid;
    /**
     * File naming pattern for exported PNGs
     */
    std::shared_ptr<std::string> png_file_pattern;
    /**
     * Height of the world grid in pixels.
     */
    int64_t world_grid_height;
    /**
     * Width of the world grid in pixels.
     */
    int64_t world_grid_width;
    /**
     * An enum that describes how levels are organized in this project (ie. linearly or in a 2D
     * space). Possible values: `Free`, `GridVania`, `LinearHorizontal`, `LinearVertical`
     */
    world_layout world_layout;
};
}

namespace nlohmann {
void from_json(const json & j, quicktype::field_definition & x);
void to_json(json & j, const quicktype::field_definition & x);

void from_json(const json & j, quicktype::entity_definition & x);
void to_json(json & j, const quicktype::entity_definition & x);

void from_json(const json & j, quicktype::enum_value_definition & x);
void to_json(json & j, const quicktype::enum_value_definition & x);

void from_json(const json & j, quicktype::enum_definition & x);
void to_json(json & j, const quicktype::enum_definition & x);

void from_json(const json & j, quicktype::auto_layer_rule_definition & x);
void to_json(json & j, const quicktype::auto_layer_rule_definition & x);

void from_json(const json & j, quicktype::auto_layer_rule_group & x);
void to_json(json & j, const quicktype::auto_layer_rule_group & x);

void from_json(const json & j, quicktype::int_grid_value_definition & x);
void to_json(json & j, const quicktype::int_grid_value_definition & x);

void from_json(const json & j, quicktype::layer_definition & x);
void to_json(json & j, const quicktype::layer_definition & x);

void from_json(const json & j, quicktype::tileset_definition & x);
void to_json(json & j, const quicktype::tileset_definition & x);

void from_json(const json & j, quicktype::definitions & x);
void to_json(json & j, const quicktype::definitions & x);

void from_json(const json & j, quicktype::level_background_position & x);
void to_json(json & j, const quicktype::level_background_position & x);

void from_json(const json & j, quicktype::field_instance & x);
void to_json(json & j, const quicktype::field_instance & x);

void from_json(const json & j, quicktype::tile_instance & x);
void to_json(json & j, const quicktype::tile_instance & x);

void from_json(const json & j, quicktype::entity_instance_tile & x);
void to_json(json & j, const quicktype::entity_instance_tile & x);

void from_json(const json & j, quicktype::entity_instance & x);
void to_json(json & j, const quicktype::entity_instance & x);

void from_json(const json & j, quicktype::int_grid_value_instance & x);
void to_json(json & j, const quicktype::int_grid_value_instance & x);

void from_json(const json & j, quicktype::layer_instance & x);
void to_json(json & j, const quicktype::layer_instance & x);

void from_json(const json & j, quicktype::neighbour_level & x);
void to_json(json & j, const quicktype::neighbour_level & x);

void from_json(const json & j, quicktype::level & x);
void to_json(json & j, const quicktype::level & x);

void from_json(const json & j, quicktype::ldtk & x);
void to_json(json & j, const quicktype::ldtk & x);

void from_json(const json & j, quicktype::editor_display_mode & x);
void to_json(json & j, const quicktype::editor_display_mode & x);

void from_json(const json & j, quicktype::editor_display_pos & x);
void to_json(json & j, const quicktype::editor_display_pos & x);

void from_json(const json & j, quicktype::text_language_mode & x);
void to_json(json & j, const quicktype::text_language_mode & x);

void from_json(const json & j, quicktype::limit_behavior & x);
void to_json(json & j, const quicktype::limit_behavior & x);

void from_json(const json & j, quicktype::limit_scope & x);
void to_json(json & j, const quicktype::limit_scope & x);

void from_json(const json & j, quicktype::render_mode & x);
void to_json(json & j, const quicktype::render_mode & x);

void from_json(const json & j, quicktype::tile_render_mode & x);
void to_json(json & j, const quicktype::tile_render_mode & x);

void from_json(const json & j, quicktype::checker & x);
void to_json(json & j, const quicktype::checker & x);

void from_json(const json & j, quicktype::tile_mode & x);
void to_json(json & j, const quicktype::tile_mode & x);

void from_json(const json & j, quicktype::type & x);
void to_json(json & j, const quicktype::type & x);

void from_json(const json & j, quicktype::flag & x);
void to_json(json & j, const quicktype::flag & x);

void from_json(const json & j, quicktype::image_export_mode & x);
void to_json(json & j, const quicktype::image_export_mode & x);

void from_json(const json & j, quicktype::bg_pos & x);
void to_json(json & j, const quicktype::bg_pos & x);

void from_json(const json & j, quicktype::world_layout & x);
void to_json(json & j, const quicktype::world_layout & x);

inline void from_json(const json & j, quicktype::field_definition& x) {
    x.type = j.at("__type").get<std::string>();
    x.accept_file_types = quicktype::get_optional<std::vector<std::string>>(j, "acceptFileTypes");
    x.array_max_length = quicktype::get_optional<int64_t>(j, "arrayMaxLength");
    x.array_min_length = quicktype::get_optional<int64_t>(j, "arrayMinLength");
    x.can_be_null = j.at("canBeNull").get<bool>();
    x.default_override = quicktype::get_untyped(j, "defaultOverride");
    x.editor_always_show = j.at("editorAlwaysShow").get<bool>();
    x.editor_cut_long_values = j.at("editorCutLongValues").get<bool>();
    x.editor_display_mode = j.at("editorDisplayMode").get<quicktype::editor_display_mode>();
    x.editor_display_pos = j.at("editorDisplayPos").get<quicktype::editor_display_pos>();
    x.identifier = j.at("identifier").get<std::string>();
    x.is_array = j.at("isArray").get<bool>();
    x.max = quicktype::get_optional<double>(j, "max");
    x.min = quicktype::get_optional<double>(j, "min");
    x.regex = quicktype::get_optional<std::string>(j, "regex");
    x.text_language_mode = quicktype::get_optional<quicktype::text_language_mode>(j, "textLanguageMode");
    x.field_definition_type = quicktype::get_untyped(j, "type");
    x.uid = j.at("uid").get<int64_t>();
}

inline void to_json(json & j, const quicktype::field_definition & x) {
    j = json::object();
    j["__type"] = x.type;
    if (x.accept_file_types) {
        j["acceptFileTypes"] = x.accept_file_types;
    }
    if (x.array_max_length) {
        j["arrayMaxLength"] = x.array_max_length;
    }
    if (x.array_min_length) {
        j["arrayMinLength"] = x.array_min_length;
    }
    j["canBeNull"] = x.can_be_null;
    if (x.default_override) {
        j["defaultOverride"] = x.default_override;
    }
    j["editorAlwaysShow"] = x.editor_always_show;
    j["editorCutLongValues"] = x.editor_cut_long_values;
    j["editorDisplayMode"] = x.editor_display_mode;
    j["editorDisplayPos"] = x.editor_display_pos;
    j["identifier"] = x.identifier;
    j["isArray"] = x.is_array;
    if (x.max) {
        j["max"] = x.max;
    }
    if (x.min) {
        j["min"] = x.min;
    }
    if (x.regex) {
        j["regex"] = x.regex;
    }
    if (x.text_language_mode) {
        j["textLanguageMode"] = x.text_language_mode;
    }
    j["type"] = x.field_definition_type;
    j["uid"] = x.uid;
}

inline void from_json(const json & j, quicktype::entity_definition& x) {
    x.color = j.at("color").get<std::string>();
    x.field_defs = j.at("fieldDefs").get<std::vector<quicktype::field_definition>>();
    x.fill_opacity = j.at("fillOpacity").get<double>();
    x.height = j.at("height").get<int64_t>();
    x.hollow = j.at("hollow").get<bool>();
    x.identifier = j.at("identifier").get<std::string>();
    x.keep_aspect_ratio = j.at("keepAspectRatio").get<bool>();
    x.limit_behavior = j.at("limitBehavior").get<quicktype::limit_behavior>();
    x.limit_scope = j.at("limitScope").get<quicktype::limit_scope>();
    x.line_opacity = j.at("lineOpacity").get<double>();
    x.max_count = j.at("maxCount").get<int64_t>();
    x.pivot_x = j.at("pivotX").get<double>();
    x.pivot_y = j.at("pivotY").get<double>();
    x.render_mode = j.at("renderMode").get<quicktype::render_mode>();
    x.resizable_x = j.at("resizableX").get<bool>();
    x.resizable_y = j.at("resizableY").get<bool>();
    x.show_name = j.at("showName").get<bool>();
    x.tags = j.at("tags").get<std::vector<std::string>>();
    x.tile_id = quicktype::get_optional<int64_t>(j, "tileId");
    x.tile_render_mode = j.at("tileRenderMode").get<quicktype::tile_render_mode>();
    x.tileset_id = quicktype::get_optional<int64_t>(j, "tilesetId");
    x.uid = j.at("uid").get<int64_t>();
    x.width = j.at("width").get<int64_t>();
}

inline void to_json(json & j, const quicktype::entity_definition & x) {
    j = json::object();
    j["color"] = x.color;
    j["fieldDefs"] = x.field_defs;
    j["fillOpacity"] = x.fill_opacity;
    j["height"] = x.height;
    j["hollow"] = x.hollow;
    j["identifier"] = x.identifier;
    j["keepAspectRatio"] = x.keep_aspect_ratio;
    j["limitBehavior"] = x.limit_behavior;
    j["limitScope"] = x.limit_scope;
    j["lineOpacity"] = x.line_opacity;
    j["maxCount"] = x.max_count;
    j["pivotX"] = x.pivot_x;
    j["pivotY"] = x.pivot_y;
    j["renderMode"] = x.render_mode;
    j["resizableX"] = x.resizable_x;
    j["resizableY"] = x.resizable_y;
    j["showName"] = x.show_name;
    j["tags"] = x.tags;
    if (x.tile_id) {
        j["tileId"] = x.tile_id;
    }
    j["tileRenderMode"] = x.tile_render_mode;
    if (x.tileset_id) {
        j["tilesetId"] = x.tileset_id;
    }
    j["uid"] = x.uid;
    j["width"] = x.width;
}

inline void from_json(const json & j, quicktype::enum_value_definition& x) {
    x.tile_src_rect = quicktype::get_optional<std::vector<int64_t>>(j, "__tileSrcRect");
    x.color = j.at("color").get<int64_t>();
    x.id = j.at("id").get<std::string>();
    x.tile_id = quicktype::get_optional<int64_t>(j, "tileId");
}

inline void to_json(json & j, const quicktype::enum_value_definition & x) {
    j = json::object();
    if (x.tile_src_rect) {
        j["__tileSrcRect"] = x.tile_src_rect;
    }
    j["color"] = x.color;
    j["id"] = x.id;
    if (x.tile_id) {
        j["tileId"] = x.tile_id;
    }
}

inline void from_json(const json & j, quicktype::enum_definition& x) {
    x.external_file_checksum = quicktype::get_optional<std::string>(j, "externalFileChecksum");
    x.external_rel_path = quicktype::get_optional<std::string>(j, "externalRelPath");
    x.icon_tileset_uid = quicktype::get_optional<int64_t>(j, "iconTilesetUid");
    x.identifier = j.at("identifier").get<std::string>();
    x.uid = j.at("uid").get<int64_t>();
    x.values = j.at("values").get<std::vector<quicktype::enum_value_definition>>();
}

inline void to_json(json & j, const quicktype::enum_definition & x) {
    j = json::object();
    if (x.external_file_checksum) {
        j["externalFileChecksum"] = x.external_file_checksum;
    }
    if (x.external_rel_path) {
        j["externalRelPath"] = x.external_rel_path;
    }
    if (x.icon_tileset_uid) {
        j["iconTilesetUid"] = x.icon_tileset_uid;
    }
    j["identifier"] = x.identifier;
    j["uid"] = x.uid;
    j["values"] = x.values;
}

inline void from_json(const json & j, quicktype::auto_layer_rule_definition& x) {
    x.active = j.at("active").get<bool>();
    x.break_on_match = j.at("breakOnMatch").get<bool>();
    x.chance = j.at("chance").get<double>();
    x.checker = j.at("checker").get<quicktype::checker>();
    x.flip_x = j.at("flipX").get<bool>();
    x.flip_y = j.at("flipY").get<bool>();
    x.out_of_bounds_value = quicktype::get_optional<int64_t>(j, "outOfBoundsValue");
    x.pattern = j.at("pattern").get<std::vector<int64_t>>();
    x.perlin_active = j.at("perlinActive").get<bool>();
    x.perlin_octaves = j.at("perlinOctaves").get<double>();
    x.perlin_scale = j.at("perlinScale").get<double>();
    x.perlin_seed = j.at("perlinSeed").get<double>();
    x.pivot_x = j.at("pivotX").get<double>();
    x.pivot_y = j.at("pivotY").get<double>();
    x.size = j.at("size").get<int64_t>();
    x.tile_ids = j.at("tileIds").get<std::vector<int64_t>>();
    x.tile_mode = j.at("tileMode").get<quicktype::tile_mode>();
    x.uid = j.at("uid").get<int64_t>();
    x.x_modulo = j.at("xModulo").get<int64_t>();
    x.y_modulo = j.at("yModulo").get<int64_t>();
}

inline void to_json(json & j, const quicktype::auto_layer_rule_definition & x) {
    j = json::object();
    j["active"] = x.active;
    j["breakOnMatch"] = x.break_on_match;
    j["chance"] = x.chance;
    j["checker"] = x.checker;
    j["flipX"] = x.flip_x;
    j["flipY"] = x.flip_y;
    if (x.out_of_bounds_value) {
        j["outOfBoundsValue"] = x.out_of_bounds_value;
    }
    j["pattern"] = x.pattern;
    j["perlinActive"] = x.perlin_active;
    j["perlinOctaves"] = x.perlin_octaves;
    j["perlinScale"] = x.perlin_scale;
    j["perlinSeed"] = x.perlin_seed;
    j["pivotX"] = x.pivot_x;
    j["pivotY"] = x.pivot_y;
    j["size"] = x.size;
    j["tileIds"] = x.tile_ids;
    j["tileMode"] = x.tile_mode;
    j["uid"] = x.uid;
    j["xModulo"] = x.x_modulo;
    j["yModulo"] = x.y_modulo;
}

inline void from_json(const json & j, quicktype::auto_layer_rule_group& x) {
    x.active = j.at("active").get<bool>();
    x.collapsed = j.at("collapsed").get<bool>();
    x.is_optional = j.at("isOptional").get<bool>();
    x.name = j.at("name").get<std::string>();
    x.rules = j.at("rules").get<std::vector<quicktype::auto_layer_rule_definition>>();
    x.uid = j.at("uid").get<int64_t>();
}

inline void to_json(json & j, const quicktype::auto_layer_rule_group & x) {
    j = json::object();
    j["active"] = x.active;
    j["collapsed"] = x.collapsed;
    j["isOptional"] = x.is_optional;
    j["name"] = x.name;
    j["rules"] = x.rules;
    j["uid"] = x.uid;
}

inline void from_json(const json & j, quicktype::int_grid_value_definition& x) {
    x.color = j.at("color").get<std::string>();
    x.identifier = quicktype::get_optional<std::string>(j, "identifier");
    x.value = j.at("value").get<int64_t>();
}

inline void to_json(json & j, const quicktype::int_grid_value_definition & x) {
    j = json::object();
    j["color"] = x.color;
    if (x.identifier) {
        j["identifier"] = x.identifier;
    }
    j["value"] = x.value;
}

inline void from_json(const json & j, quicktype::layer_definition& x) {
    x.type = j.at("__type").get<std::string>();
    x.auto_rule_groups = j.at("autoRuleGroups").get<std::vector<quicktype::auto_layer_rule_group>>();
    x.auto_source_layer_def_uid = quicktype::get_optional<int64_t>(j, "autoSourceLayerDefUid");
    x.auto_tileset_def_uid = quicktype::get_optional<int64_t>(j, "autoTilesetDefUid");
    x.display_opacity = j.at("displayOpacity").get<double>();
    x.excluded_tags = j.at("excludedTags").get<std::vector<std::string>>();
    x.grid_size = j.at("gridSize").get<int64_t>();
    x.identifier = j.at("identifier").get<std::string>();
    x.int_grid_values = j.at("intGridValues").get<std::vector<quicktype::int_grid_value_definition>>();
    x.px_offset_x = j.at("pxOffsetX").get<int64_t>();
    x.px_offset_y = j.at("pxOffsetY").get<int64_t>();
    x.required_tags = j.at("requiredTags").get<std::vector<std::string>>();
    x.tile_pivot_x = j.at("tilePivotX").get<double>();
    x.tile_pivot_y = j.at("tilePivotY").get<double>();
    x.tileset_def_uid = quicktype::get_optional<int64_t>(j, "tilesetDefUid");
    x.layer_definition_type = j.at("type").get<quicktype::type>();
    x.uid = j.at("uid").get<int64_t>();
}

inline void to_json(json & j, const quicktype::layer_definition & x) {
    j = json::object();
    j["__type"] = x.type;
    j["autoRuleGroups"] = x.auto_rule_groups;
    if (x.auto_source_layer_def_uid) {
        j["autoSourceLayerDefUid"] = x.auto_source_layer_def_uid;
    }
    if (x.auto_tileset_def_uid) {
        j["autoTilesetDefUid"] = x.auto_tileset_def_uid;
    }
    j["displayOpacity"] = x.display_opacity;
    j["excludedTags"] = x.excluded_tags;
    j["gridSize"] = x.grid_size;
    j["identifier"] = x.identifier;
    j["intGridValues"] = x.int_grid_values;
    j["pxOffsetX"] = x.px_offset_x;
    j["pxOffsetY"] = x.px_offset_y;
    j["requiredTags"] = x.required_tags;
    j["tilePivotX"] = x.tile_pivot_x;
    j["tilePivotY"] = x.tile_pivot_y;
    if (x.tileset_def_uid) {
        j["tilesetDefUid"] = x.tileset_def_uid;
    }
    j["type"] = x.layer_definition_type;
    j["uid"] = x.uid;
}

inline void from_json(const json & j, quicktype::tileset_definition& x) {
    x.c_hei = j.at("__cHei").get<int64_t>();
    x.c_wid = j.at("__cWid").get<int64_t>();
    x.cached_pixel_data = quicktype::get_optional<std::map<std::string, json>>(j, "cachedPixelData");
    x.custom_data = j.at("customData").get<std::vector<std::map<std::string, json>>>();
    x.enum_tags = j.at("enumTags").get<std::vector<std::map<std::string, json>>>();
    x.identifier = j.at("identifier").get<std::string>();
    x.padding = j.at("padding").get<int64_t>();
    x.px_hei = j.at("pxHei").get<int64_t>();
    x.px_wid = j.at("pxWid").get<int64_t>();
    x.rel_path = j.at("relPath").get<std::string>();
    x.saved_selections = j.at("savedSelections").get<std::vector<std::map<std::string, json>>>();
    x.spacing = j.at("spacing").get<int64_t>();
    x.tags_source_enum_uid = quicktype::get_optional<int64_t>(j, "tagsSourceEnumUid");
    x.tile_grid_size = j.at("tileGridSize").get<int64_t>();
    x.uid = j.at("uid").get<int64_t>();
}

inline void to_json(json & j, const quicktype::tileset_definition & x) {
    j = json::object();
    j["__cHei"] = x.c_hei;
    j["__cWid"] = x.c_wid;
    if (x.cached_pixel_data) {
        j["cachedPixelData"] = x.cached_pixel_data;
    }
    j["customData"] = x.custom_data;
    j["enumTags"] = x.enum_tags;
    j["identifier"] = x.identifier;
    j["padding"] = x.padding;
    j["pxHei"] = x.px_hei;
    j["pxWid"] = x.px_wid;
    j["relPath"] = x.rel_path;
    j["savedSelections"] = x.saved_selections;
    j["spacing"] = x.spacing;
    if (x.tags_source_enum_uid) {
        j["tagsSourceEnumUid"] = x.tags_source_enum_uid;
    }
    j["tileGridSize"] = x.tile_grid_size;
    j["uid"] = x.uid;
}

inline void from_json(const json & j, quicktype::definitions& x) {
    x.entities = j.at("entities").get<std::vector<quicktype::entity_definition>>();
    x.enums = j.at("enums").get<std::vector<quicktype::enum_definition>>();
    x.external_enums = j.at("externalEnums").get<std::vector<quicktype::enum_definition>>();
    x.layers = j.at("layers").get<std::vector<quicktype::layer_definition>>();
    x.level_fields = j.at("levelFields").get<std::vector<quicktype::field_definition>>();
    x.tilesets = j.at("tilesets").get<std::vector<quicktype::tileset_definition>>();
}

inline void to_json(json & j, const quicktype::definitions & x) {
    j = json::object();
    j["entities"] = x.entities;
    j["enums"] = x.enums;
    j["externalEnums"] = x.external_enums;
    j["layers"] = x.layers;
    j["levelFields"] = x.level_fields;
    j["tilesets"] = x.tilesets;
}

inline void from_json(const json & j, quicktype::level_background_position& x) {
    x.crop_rect = j.at("cropRect").get<std::vector<double>>();
    x.scale = j.at("scale").get<std::vector<double>>();
    x.top_left_px = j.at("topLeftPx").get<std::vector<int64_t>>();
}

inline void to_json(json & j, const quicktype::level_background_position & x) {
    j = json::object();
    j["cropRect"] = x.crop_rect;
    j["scale"] = x.scale;
    j["topLeftPx"] = x.top_left_px;
}

inline void from_json(const json & j, quicktype::field_instance& x) {
    x.identifier = j.at("__identifier").get<std::string>();
    x.type = j.at("__type").get<std::string>();
    x.value = quicktype::get_untyped(j, "__value");
    x.def_uid = j.at("defUid").get<int64_t>();
    x.real_editor_values = j.at("realEditorValues").get<std::vector<json>>();
}

inline void to_json(json & j, const quicktype::field_instance & x) {
    j = json::object();
    j["__identifier"] = x.identifier;
    j["__type"] = x.type;
    j["__value"] = x.value;
    j["defUid"] = x.def_uid;
    j["realEditorValues"] = x.real_editor_values;
}

inline void from_json(const json & j, quicktype::tile_instance& x) {
    x.d = j.at("d").get<std::vector<int64_t>>();
    x.f = j.at("f").get<int64_t>();
    x.px = j.at("px").get<std::vector<int64_t>>();
    x.src = j.at("src").get<std::vector<int64_t>>();
    x.t = j.at("t").get<int64_t>();
}

inline void to_json(json & j, const quicktype::tile_instance & x) {
    j = json::object();
    j["d"] = x.d;
    j["f"] = x.f;
    j["px"] = x.px;
    j["src"] = x.src;
    j["t"] = x.t;
}

inline void from_json(const json & j, quicktype::entity_instance_tile& x) {
    x.src_rect = j.at("srcRect").get<std::vector<int64_t>>();
    x.tileset_uid = j.at("tilesetUid").get<int64_t>();
}

inline void to_json(json & j, const quicktype::entity_instance_tile & x) {
    j = json::object();
    j["srcRect"] = x.src_rect;
    j["tilesetUid"] = x.tileset_uid;
}

inline void from_json(const json & j, quicktype::entity_instance& x) {
    x.grid = j.at("__grid").get<std::vector<int64_t>>();
    x.identifier = j.at("__identifier").get<std::string>();
    x.pivot = j.at("__pivot").get<std::vector<double>>();
    x.tile = quicktype::get_optional<quicktype::entity_instance_tile>(j, "__tile");
    x.def_uid = j.at("defUid").get<int64_t>();
    x.field_instances = j.at("fieldInstances").get<std::vector<quicktype::field_instance>>();
    x.height = j.at("height").get<int64_t>();
    x.px = j.at("px").get<std::vector<int64_t>>();
    x.width = j.at("width").get<int64_t>();
}

inline void to_json(json & j, const quicktype::entity_instance & x) {
    j = json::object();
    j["__grid"] = x.grid;
    j["__identifier"] = x.identifier;
    j["__pivot"] = x.pivot;
    if (x.tile) {
        j["__tile"] = x.tile;
    }
    j["defUid"] = x.def_uid;
    j["fieldInstances"] = x.field_instances;
    j["height"] = x.height;
    j["px"] = x.px;
    j["width"] = x.width;
}

inline void from_json(const json & j, quicktype::int_grid_value_instance& x) {
    x.coord_id = j.at("coordId").get<int64_t>();
    x.v = j.at("v").get<int64_t>();
}

inline void to_json(json & j, const quicktype::int_grid_value_instance & x) {
    j = json::object();
    j["coordId"] = x.coord_id;
    j["v"] = x.v;
}

inline void from_json(const json & j, quicktype::layer_instance& x) {
    x.c_hei = j.at("__cHei").get<int64_t>();
    x.c_wid = j.at("__cWid").get<int64_t>();
    x.grid_size = j.at("__gridSize").get<int64_t>();
    x.identifier = j.at("__identifier").get<std::string>();
    x.opacity = j.at("__opacity").get<double>();
    x.px_total_offset_x = j.at("__pxTotalOffsetX").get<int64_t>();
    x.px_total_offset_y = j.at("__pxTotalOffsetY").get<int64_t>();
    x.tileset_def_uid = quicktype::get_optional<int64_t>(j, "__tilesetDefUid");
    x.tileset_rel_path = quicktype::get_optional<std::string>(j, "__tilesetRelPath");
    x.type = j.at("__type").get<std::string>();
    x.auto_layer_tiles = j.at("autoLayerTiles").get<std::vector<quicktype::tile_instance>>();
    x.entity_instances = j.at("entityInstances").get<std::vector<quicktype::entity_instance>>();
    x.grid_tiles = j.at("gridTiles").get<std::vector<quicktype::tile_instance>>();
    x.int_grid = quicktype::get_optional<std::vector<quicktype::int_grid_value_instance>>(j, "intGrid");
    x.int_grid_csv = j.at("intGridCsv").get<std::vector<int64_t>>();
    x.layer_def_uid = j.at("layerDefUid").get<int64_t>();
    x.level_id = j.at("levelId").get<int64_t>();
    x.optional_rules = j.at("optionalRules").get<std::vector<int64_t>>();
    x.override_tileset_uid = quicktype::get_optional<int64_t>(j, "overrideTilesetUid");
    x.px_offset_x = j.at("pxOffsetX").get<int64_t>();
    x.px_offset_y = j.at("pxOffsetY").get<int64_t>();
    x.seed = j.at("seed").get<int64_t>();
    x.visible = j.at("visible").get<bool>();
}

inline void to_json(json & j, const quicktype::layer_instance & x) {
    j = json::object();
    j["__cHei"] = x.c_hei;
    j["__cWid"] = x.c_wid;
    j["__gridSize"] = x.grid_size;
    j["__identifier"] = x.identifier;
    j["__opacity"] = x.opacity;
    j["__pxTotalOffsetX"] = x.px_total_offset_x;
    j["__pxTotalOffsetY"] = x.px_total_offset_y;
    if (x.tileset_def_uid) {
        j["__tilesetDefUid"] = x.tileset_def_uid;
    }
    if (x.tileset_rel_path) {
        j["__tilesetRelPath"] = x.tileset_rel_path;
    }
    j["__type"] = x.type;
    j["autoLayerTiles"] = x.auto_layer_tiles;
    j["entityInstances"] = x.entity_instances;
    j["gridTiles"] = x.grid_tiles;
    if (x.int_grid) {
        j["intGrid"] = x.int_grid;
    }
    j["intGridCsv"] = x.int_grid_csv;
    j["layerDefUid"] = x.layer_def_uid;
    j["levelId"] = x.level_id;
    j["optionalRules"] = x.optional_rules;
    if (x.override_tileset_uid) {
        j["overrideTilesetUid"] = x.override_tileset_uid;
    }
    j["pxOffsetX"] = x.px_offset_x;
    j["pxOffsetY"] = x.px_offset_y;
    j["seed"] = x.seed;
    j["visible"] = x.visible;
}

inline void from_json(const json & j, quicktype::neighbour_level& x) {
    x.dir = j.at("dir").get<std::string>();
    x.level_uid = j.at("levelUid").get<int64_t>();
}

inline void to_json(json & j, const quicktype::neighbour_level & x) {
    j = json::object();
    j["dir"] = x.dir;
    j["levelUid"] = x.level_uid;
}

inline void from_json(const json & j, quicktype::level& x) {
    x.bg_color = j.at("__bgColor").get<std::string>();
    x.bg_pos = quicktype::get_optional<quicktype::level_background_position>(j, "__bgPos");
    x.neighbours = j.at("__neighbours").get<std::vector<quicktype::neighbour_level>>();
    x.level_bg_color = quicktype::get_optional<std::string>(j, "bgColor");
    x.bg_pivot_x = j.at("bgPivotX").get<double>();
    x.bg_pivot_y = j.at("bgPivotY").get<double>();
    x.level_bg_pos = quicktype::get_optional<quicktype::bg_pos>(j, "bgPos");
    x.bg_rel_path = quicktype::get_optional<std::string>(j, "bgRelPath");
    x.external_rel_path = quicktype::get_optional<std::string>(j, "externalRelPath");
    x.field_instances = j.at("fieldInstances").get<std::vector<quicktype::field_instance>>();
    x.identifier = j.at("identifier").get<std::string>();
    x.layer_instances = quicktype::get_optional<std::vector<quicktype::layer_instance>>(j, "layerInstances");
    x.px_hei = j.at("pxHei").get<int64_t>();
    x.px_wid = j.at("pxWid").get<int64_t>();
    x.uid = j.at("uid").get<int64_t>();
    x.use_auto_identifier = j.at("useAutoIdentifier").get<bool>();
    x.world_x = j.at("worldX").get<int64_t>();
    x.world_y = j.at("worldY").get<int64_t>();
}

inline void to_json(json & j, const quicktype::level & x) {
    j = json::object();
    j["__bgColor"] = x.bg_color;
    if (x.bg_pos) {
        j["__bgPos"] = x.bg_pos;
    }
    j["__neighbours"] = x.neighbours;
    if (x.level_bg_color) {
        j["bgColor"] = x.level_bg_color;
    }
    j["bgPivotX"] = x.bg_pivot_x;
    j["bgPivotY"] = x.bg_pivot_y;
    if (x.level_bg_pos) {
        j["bgPos"] = x.level_bg_pos;
    }
    if (x.bg_rel_path) {
        j["bgRelPath"] = x.bg_rel_path;
    }
    if (x.external_rel_path) {
        j["externalRelPath"] = x.external_rel_path;
    }
    j["fieldInstances"] = x.field_instances;
    j["identifier"] = x.identifier;
    if (x.layer_instances) {
        j["layerInstances"] = x.layer_instances;
    }
    j["pxHei"] = x.px_hei;
    j["pxWid"] = x.px_wid;
    j["uid"] = x.uid;
    j["useAutoIdentifier"] = x.use_auto_identifier;
    j["worldX"] = x.world_x;
    j["worldY"] = x.world_y;
}

inline void from_json(const json & j, quicktype::ldtk& x) {
    x.backup_limit = j.at("backupLimit").get<int64_t>();
    x.backup_on_save = j.at("backupOnSave").get<bool>();
    x.bg_color = j.at("bgColor").get<std::string>();
    x.default_grid_size = j.at("defaultGridSize").get<int64_t>();
    x.default_level_bg_color = j.at("defaultLevelBgColor").get<std::string>();
    x.default_level_height = j.at("defaultLevelHeight").get<int64_t>();
    x.default_level_width = j.at("defaultLevelWidth").get<int64_t>();
    x.default_pivot_x = j.at("defaultPivotX").get<double>();
    x.default_pivot_y = j.at("defaultPivotY").get<double>();
    x.defs = j.at("defs").get<quicktype::definitions>();
    x.export_png = quicktype::get_optional<bool>(j, "exportPng");
    x.export_tiled = j.at("exportTiled").get<bool>();
    x.external_levels = j.at("externalLevels").get<bool>();
    x.flags = j.at("flags").get<std::vector<quicktype::flag>>();
    x.image_export_mode = j.at("imageExportMode").get<quicktype::image_export_mode>();
    x.json_version = j.at("jsonVersion").get<std::string>();
    x.level_name_pattern = j.at("levelNamePattern").get<std::string>();
    x.levels = j.at("levels").get<std::vector<quicktype::level>>();
    x.minify_json = j.at("minifyJson").get<bool>();
    x.next_uid = j.at("nextUid").get<int64_t>();
    x.png_file_pattern = quicktype::get_optional<std::string>(j, "pngFilePattern");
    x.world_grid_height = j.at("worldGridHeight").get<int64_t>();
    x.world_grid_width = j.at("worldGridWidth").get<int64_t>();
    x.world_layout = j.at("worldLayout").get<quicktype::world_layout>();
}

inline void to_json(json & j, const quicktype::ldtk & x) {
    j = json::object();
    j["backupLimit"] = x.backup_limit;
    j["backupOnSave"] = x.backup_on_save;
    j["bgColor"] = x.bg_color;
    j["defaultGridSize"] = x.default_grid_size;
    j["defaultLevelBgColor"] = x.default_level_bg_color;
    j["defaultLevelHeight"] = x.default_level_height;
    j["defaultLevelWidth"] = x.default_level_width;
    j["defaultPivotX"] = x.default_pivot_x;
    j["defaultPivotY"] = x.default_pivot_y;
    j["defs"] = x.defs;
    if (x.export_png) {
        j["exportPng"] = x.export_png;
    }
    j["exportTiled"] = x.export_tiled;
    j["externalLevels"] = x.external_levels;
    j["flags"] = x.flags;
    j["imageExportMode"] = x.image_export_mode;
    j["jsonVersion"] = x.json_version;
    j["levelNamePattern"] = x.level_name_pattern;
    j["levels"] = x.levels;
    j["minifyJson"] = x.minify_json;
    j["nextUid"] = x.next_uid;
    if (x.png_file_pattern) {
        j["pngFilePattern"] = x.png_file_pattern;
    }
    j["worldGridHeight"] = x.world_grid_height;
    j["worldGridWidth"] = x.world_grid_width;
    j["worldLayout"] = x.world_layout;
}

inline void from_json(const json & j, quicktype::editor_display_mode & x) {
    if (j == "EntityTile") x = quicktype::editor_display_mode::entity_tile;
    else if (j == "Hidden") x = quicktype::editor_display_mode::hidden;
    else if (j == "NameAndValue") x = quicktype::editor_display_mode::name_and_value;
    else if (j == "PointPath") x = quicktype::editor_display_mode::point_path;
    else if (j == "PointPathLoop") x = quicktype::editor_display_mode::point_path_loop;
    else if (j == "PointStar") x = quicktype::editor_display_mode::point_star;
    else if (j == "Points") x = quicktype::editor_display_mode::points;
    else if (j == "RadiusGrid") x = quicktype::editor_display_mode::radius_grid;
    else if (j == "RadiusPx") x = quicktype::editor_display_mode::radius_px;
    else if (j == "ValueOnly") x = quicktype::editor_display_mode::value_only;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::editor_display_mode & x) {
    switch (x) {
        case quicktype::editor_display_mode::entity_tile: j = "EntityTile"; break;
        case quicktype::editor_display_mode::hidden: j = "Hidden"; break;
        case quicktype::editor_display_mode::name_and_value: j = "NameAndValue"; break;
        case quicktype::editor_display_mode::point_path: j = "PointPath"; break;
        case quicktype::editor_display_mode::point_path_loop: j = "PointPathLoop"; break;
        case quicktype::editor_display_mode::point_star: j = "PointStar"; break;
        case quicktype::editor_display_mode::points: j = "Points"; break;
        case quicktype::editor_display_mode::radius_grid: j = "RadiusGrid"; break;
        case quicktype::editor_display_mode::radius_px: j = "RadiusPx"; break;
        case quicktype::editor_display_mode::value_only: j = "ValueOnly"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::editor_display_pos & x) {
    if (j == "Above") x = quicktype::editor_display_pos::above;
    else if (j == "Beneath") x = quicktype::editor_display_pos::beneath;
    else if (j == "Center") x = quicktype::editor_display_pos::center;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::editor_display_pos & x) {
    switch (x) {
        case quicktype::editor_display_pos::above: j = "Above"; break;
        case quicktype::editor_display_pos::beneath: j = "Beneath"; break;
        case quicktype::editor_display_pos::center: j = "Center"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::text_language_mode & x) {
    if (j == "LangC") x = quicktype::text_language_mode::lang_c;
    else if (j == "LangHaxe") x = quicktype::text_language_mode::lang_haxe;
    else if (j == "LangJS") x = quicktype::text_language_mode::lang_js;
    else if (j == "LangJson") x = quicktype::text_language_mode::lang_json;
    else if (j == "LangLua") x = quicktype::text_language_mode::lang_lua;
    else if (j == "LangMarkdown") x = quicktype::text_language_mode::lang_markdown;
    else if (j == "LangPython") x = quicktype::text_language_mode::lang_python;
    else if (j == "LangRuby") x = quicktype::text_language_mode::lang_ruby;
    else if (j == "LangXml") x = quicktype::text_language_mode::lang_xml;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::text_language_mode & x) {
    switch (x) {
        case quicktype::text_language_mode::lang_c: j = "LangC"; break;
        case quicktype::text_language_mode::lang_haxe: j = "LangHaxe"; break;
        case quicktype::text_language_mode::lang_js: j = "LangJS"; break;
        case quicktype::text_language_mode::lang_json: j = "LangJson"; break;
        case quicktype::text_language_mode::lang_lua: j = "LangLua"; break;
        case quicktype::text_language_mode::lang_markdown: j = "LangMarkdown"; break;
        case quicktype::text_language_mode::lang_python: j = "LangPython"; break;
        case quicktype::text_language_mode::lang_ruby: j = "LangRuby"; break;
        case quicktype::text_language_mode::lang_xml: j = "LangXml"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::limit_behavior & x) {
    if (j == "DiscardOldOnes") x = quicktype::limit_behavior::discard_old_ones;
    else if (j == "MoveLastOne") x = quicktype::limit_behavior::move_last_one;
    else if (j == "PreventAdding") x = quicktype::limit_behavior::prevent_adding;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::limit_behavior & x) {
    switch (x) {
        case quicktype::limit_behavior::discard_old_ones: j = "DiscardOldOnes"; break;
        case quicktype::limit_behavior::move_last_one: j = "MoveLastOne"; break;
        case quicktype::limit_behavior::prevent_adding: j = "PreventAdding"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::limit_scope & x) {
    if (j == "PerLayer") x = quicktype::limit_scope::per_layer;
    else if (j == "PerLevel") x = quicktype::limit_scope::per_level;
    else if (j == "PerWorld") x = quicktype::limit_scope::per_world;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::limit_scope & x) {
    switch (x) {
        case quicktype::limit_scope::per_layer: j = "PerLayer"; break;
        case quicktype::limit_scope::per_level: j = "PerLevel"; break;
        case quicktype::limit_scope::per_world: j = "PerWorld"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::render_mode & x) {
    if (j == "Cross") x = quicktype::render_mode::cross;
    else if (j == "Ellipse") x = quicktype::render_mode::ellipse;
    else if (j == "Rectangle") x = quicktype::render_mode::rectangle;
    else if (j == "Tile") x = quicktype::render_mode::tile;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::render_mode & x) {
    switch (x) {
        case quicktype::render_mode::cross: j = "Cross"; break;
        case quicktype::render_mode::ellipse: j = "Ellipse"; break;
        case quicktype::render_mode::rectangle: j = "Rectangle"; break;
        case quicktype::render_mode::tile: j = "Tile"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::tile_render_mode & x) {
    if (j == "Cover") x = quicktype::tile_render_mode::cover;
    else if (j == "FitInside") x = quicktype::tile_render_mode::fit_inside;
    else if (j == "Repeat") x = quicktype::tile_render_mode::repeat;
    else if (j == "Stretch") x = quicktype::tile_render_mode::stretch;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::tile_render_mode & x) {
    switch (x) {
        case quicktype::tile_render_mode::cover: j = "Cover"; break;
        case quicktype::tile_render_mode::fit_inside: j = "FitInside"; break;
        case quicktype::tile_render_mode::repeat: j = "Repeat"; break;
        case quicktype::tile_render_mode::stretch: j = "Stretch"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::checker & x) {
    if (j == "Horizontal") x = quicktype::checker::horizontal;
    else if (j == "None") x = quicktype::checker::none;
    else if (j == "Vertical") x = quicktype::checker::vertical;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::checker & x) {
    switch (x) {
        case quicktype::checker::horizontal: j = "Horizontal"; break;
        case quicktype::checker::none: j = "None"; break;
        case quicktype::checker::vertical: j = "Vertical"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::tile_mode & x) {
    if (j == "Single") x = quicktype::tile_mode::single;
    else if (j == "Stamp") x = quicktype::tile_mode::stamp;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::tile_mode & x) {
    switch (x) {
        case quicktype::tile_mode::single: j = "Single"; break;
        case quicktype::tile_mode::stamp: j = "Stamp"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::type & x) {
    if (j == "AutoLayer") x = quicktype::type::auto_layer;
    else if (j == "Entities") x = quicktype::type::entities;
    else if (j == "IntGrid") x = quicktype::type::int_grid;
    else if (j == "Tiles") x = quicktype::type::tiles;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::type & x) {
    switch (x) {
        case quicktype::type::auto_layer: j = "AutoLayer"; break;
        case quicktype::type::entities: j = "Entities"; break;
        case quicktype::type::int_grid: j = "IntGrid"; break;
        case quicktype::type::tiles: j = "Tiles"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::flag & x) {
    if (j == "DiscardPreCsvIntGrid") x = quicktype::flag::discard_pre_csv_int_grid;
    else if (j == "IgnoreBackupSuggest") x = quicktype::flag::ignore_backup_suggest;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::flag & x) {
    switch (x) {
        case quicktype::flag::discard_pre_csv_int_grid: j = "DiscardPreCsvIntGrid"; break;
        case quicktype::flag::ignore_backup_suggest: j = "IgnoreBackupSuggest"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::image_export_mode & x) {
    if (j == "None") x = quicktype::image_export_mode::none;
    else if (j == "OneImagePerLayer") x = quicktype::image_export_mode::one_image_per_layer;
    else if (j == "OneImagePerLevel") x = quicktype::image_export_mode::one_image_per_level;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::image_export_mode & x) {
    switch (x) {
        case quicktype::image_export_mode::none: j = "None"; break;
        case quicktype::image_export_mode::one_image_per_layer: j = "OneImagePerLayer"; break;
        case quicktype::image_export_mode::one_image_per_level: j = "OneImagePerLevel"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::bg_pos & x) {
    if (j == "Contain") x = quicktype::bg_pos::contain;
    else if (j == "Cover") x = quicktype::bg_pos::cover;
    else if (j == "CoverDirty") x = quicktype::bg_pos::cover_dirty;
    else if (j == "Unscaled") x = quicktype::bg_pos::unscaled;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::bg_pos & x) {
    switch (x) {
        case quicktype::bg_pos::contain: j = "Contain"; break;
        case quicktype::bg_pos::cover: j = "Cover"; break;
        case quicktype::bg_pos::cover_dirty: j = "CoverDirty"; break;
        case quicktype::bg_pos::unscaled: j = "Unscaled"; break;
        default: throw "This should not happen";
    }
}

inline void from_json(const json & j, quicktype::world_layout & x) {
    if (j == "Free") x = quicktype::world_layout::free;
    else if (j == "GridVania") x = quicktype::world_layout::grid_vania;
    else if (j == "LinearHorizontal") x = quicktype::world_layout::linear_horizontal;
    else if (j == "LinearVertical") x = quicktype::world_layout::linear_vertical;
    else throw "Input JSON does not conform to schema";
}

inline void to_json(json & j, const quicktype::world_layout & x) {
    switch (x) {
        case quicktype::world_layout::free: j = "Free"; break;
        case quicktype::world_layout::grid_vania: j = "GridVania"; break;
        case quicktype::world_layout::linear_horizontal: j = "LinearHorizontal"; break;
        case quicktype::world_layout::linear_vertical: j = "LinearVertical"; break;
        default: throw "This should not happen";
    }
}
}

#endif // ENGINE_EXT_LDTK_HPP