# DetailsMetadataExtension

A plugin which extends a blueprints variables details panel with the ability to add Metadata key/values. These keys with value can be queried to have some extra information to work with while for example serializing a property. I use with my games save/load to know which properties are time floats and need to be offset to the new time origin when the level is loaded. This plugin is useful for advanced users which need to mark blueprint variables like they can in C++ meta property meta.

In C++, a property with special meta looks like this:
```
UPROPERTY(meta = (NewMeta = "This meta key and value are now set on this variable"))
int32 MyVariable;
```

And in blueprint an added metadata key value:

![Alt text](/Screenshots/meta.png?raw=true "Metadata!")


Copyright 2020-2021 Sheffer Online Services. All Rights Reserved.

MIT Licensed