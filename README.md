# DetailsMetadataExtension

A plugin which extends a blueprints properties details panel with the ability to add Metadata key/values. These keys with value can be queried to have some extra information to work with while for example serializing a property. I use it to know which properties are time floats and need to be offset when the level is loaded. This plugin is useful for advanced users which need to mark blueprint properties like they can in C++ meta sections.

In C++, a property with special meta looks like this:

UPROPERTY(meta = (hello = "world"))
int32 MyProperty;


TODO: A blueprint example of the same thing...


Copyright 2020-2021 Sheffer Online Services. All Rights Reserved.

MIT Licensed