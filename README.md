# DetailsMetadataExtension

Editor Only Extension!

A plugin which exposes the editor only metadata that can be set per property as an extension to the properties panel. The metadata is editable and you can add new metadata key values. This can be useful for exposing special meta data key values in blueprints which change the appearance of the property or add extra functionality. It could also be useful for creating new editor extensions which harnesses metadata to display specific variables in a special way.

In C++, a property with custom meta looks like this:
```
UPROPERTY(meta = (NewMeta = "This meta key and value are now set on this variable"))
int32 MyVariable;
```

And in blueprint a custom metadata key value:

![Alt text](/Screenshots/meta.png?raw=true "Metadata!")


Copyright 2020-2021 Sheffer Online Services. All Rights Reserved.

MIT Licensed
